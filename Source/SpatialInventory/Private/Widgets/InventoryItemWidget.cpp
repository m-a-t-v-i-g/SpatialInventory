// Spatial Inventory С++ template by matvig.

#include "Widgets/InventoryItemWidget.h"
#include "Components/Border.h"
#include "Base/ItemObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"
#include "InputCoreTypes.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Refresh();
}

void UInventoryItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (!Item_Border) return;
	Item_Border->SetBrushColor(FLinearColor(0.5, 0.5, 0.5, 0.5));
}

void UInventoryItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

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
	OutOperation->Payload = ItemObject;
	OutOperation->DefaultDragVisual = this;

	OnRemoved.Broadcast(ItemObject);
	RemoveFromParent();
}

void UInventoryItemWidget::Refresh()
{
	auto ItemSize = ItemObject->GetDimensions();
	
	Size = FVector2D(ItemSize.X * TileSize, ItemSize.Y * TileSize);

	if (!Item_SizeBox) return;
	
	Item_SizeBox->SetWidthOverride(Size.X);
	Item_SizeBox->SetHeightOverride(Size.Y);
}

UDragDropOperation* UInventoryItemWidget::CreateDragItem()
{
	return nullptr;
}