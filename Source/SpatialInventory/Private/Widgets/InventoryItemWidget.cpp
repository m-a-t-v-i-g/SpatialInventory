// Spatial Inventory С++ template by matvig.

#include "Widgets/InventoryItemWidget.h"

#include "Base/ItemObject.h"
#include "Components/SizeBox.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Refresh();
}

void UInventoryItemWidget::Refresh()
{
	auto ItemSize = ItemObject->GetDimensions();
	
	Size = FVector2D(ItemSize.X * TileSize, ItemSize.Y * TileSize);

	if (!Item_SizeBox) return;
	
	Item_SizeBox->SetWidthOverride(Size.X);
	Item_SizeBox->SetHeightOverride(Size.Y);
}