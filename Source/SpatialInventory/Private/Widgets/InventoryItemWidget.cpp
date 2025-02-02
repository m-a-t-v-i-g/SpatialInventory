// Spatial Inventory С++ template by matvig.

#include "Widgets/InventoryItemWidget.h"
#include "Components/Border.h"
#include "Game/Item/ItemObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"
#include "InputCoreTypes.h"
#include "Components/Image.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Refresh();
}

void UInventoryItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!Item_Border) return;
	Item_Border->SetBrushColor(FLinearColor(0.5, 0.5, 0.5, 0.5));
}

void UInventoryItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (!Item_Border) return;
	Item_Border->SetBrushColor(FLinearColor(0.0, 0.0, 0.0, 0.35));
}

FReply UInventoryItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply DetectDragIfPressed = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		DetectDragIfPressed.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	return DetectDragIfPressed;
}

void UInventoryItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
												UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	if (!OutOperation) return;
	
	OutOperation->Payload = ItemObject;
	OutOperation->DefaultDragVisual = this;

	OnRemoved.Broadcast(ItemObject);
	RemoveFromParent();
}

void UInventoryItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!Item_Image) return;
	Item_Image->BrushDelegate.BindDynamic(this, &UInventoryItemWidget::GetItemIcon);
}

FSlateBrush UInventoryItemWidget::GetItemIcon()
{
	auto ItemIcon = ItemObject->GetIcon();
	return UWidgetBlueprintLibrary::MakeBrushFromMaterial(ItemIcon, Size.X, Size.Y);
}

void UInventoryItemWidget::Refresh()
{
	if (!ItemObject) return;
	
	auto ItemSize = ItemObject->GetDimensions();
	Size = FVector2D(ItemSize.X * TileSize, ItemSize.Y * TileSize);

	if (!Item_SizeBox) return;
	
	Item_SizeBox->SetWidthOverride(Size.X);
	Item_SizeBox->SetHeightOverride(Size.Y);
}
