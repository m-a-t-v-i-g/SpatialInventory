// Spatial Inventory С++ template by matvig.

#include "Widgets/InventoryGridWidget.h"
#include "Base/ItemObject.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/InventoryComponent.h"
#include "Widgets/InventoryItemWidget.h"

void UInventoryGridWidget::InitInventory(UInventoryComponent* GetInventoryComponent, float GetTileSize)
{
	InventoryComponent = GetInventoryComponent;
	TileSize = GetTileSize;

	if (!InventoryComponent) return;

	auto GridBorderSize = FVector2D(InventoryComponent->Columns * TileSize, InventoryComponent->Rows * TileSize);
	UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryGrid_GridBorder)->SetSize(GridBorderSize);

	CreateSegments();
	Refresh();

	InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryGridWidget::Refresh);
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
                                        int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	auto Context = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	for (auto Line : Lines)
	{
		auto GetCachedGeometry = InventoryGrid_GridBorder->GetCachedGeometry();
		auto GetLocalTopLeft = USlateBlueprintLibrary::GetLocalTopLeft(GetCachedGeometry);

		UWidgetBlueprintLibrary::DrawLine(Context, Line.Start + GetLocalTopLeft, Line.End + GetLocalTopLeft,
									FColor(125, 125, 125, 125), true, 1.0);
	}
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

void UInventoryGridWidget::CreateSegments()
{
	FLine Line;
	for (int i = 0; i <= InventoryComponent->Columns; i++)
	{
		float X = i * TileSize;
		Lines.Add(MakeLineX(Line, X, InventoryComponent->Rows * TileSize));
	}
	for (int i = 0; i <= InventoryComponent->Rows; i++)
	{
		float Y = i * TileSize;
		Lines.Add(MakeLineY(Line, Y, InventoryComponent->Columns * TileSize));
	}
}

void UInventoryGridWidget::Refresh()
{
	InventoryGrid_GridPanel->ClearChildren();

	auto GetItemsMap = InventoryComponent->GetAllItems();
	for (auto Keys : GetItemsMap)
	{
		auto KeyItem = Keys.Key;
		auto ValueTile = Keys.Value;
		auto CreateItemWidget = CreateWidget<UInventoryItemWidget>(GetOwningPlayer(),
		                                                           InventoryComponent->InventoryItemWidget);
		if (CreateItemWidget)
		{
			CreateItemWidget->TileSize = TileSize;
			CreateItemWidget->ItemObject = KeyItem;
			CreateItemWidget->OnRemoved.AddDynamic(this, &UInventoryGridWidget::OnItemRemoved);

			auto CanvasPanelSlot = Cast<UCanvasPanelSlot>(InventoryGrid_GridPanel->AddChild(CreateItemWidget));
			if (CanvasPanelSlot)
			{
				FVector2D InPosition = FVector2D(ValueTile.X * TileSize, ValueTile.Y * TileSize);
				CanvasPanelSlot->SetAutoSize(true);
				CanvasPanelSlot->SetPosition(InPosition);
			}
		}
	}
}

void UInventoryGridWidget::OnItemRemoved(UItemObject* ItemObject)
{
	InventoryComponent->RemoveItem(ItemObject);
}
