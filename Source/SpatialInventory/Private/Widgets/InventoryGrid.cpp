// Spatial Inventory С++ template by matvig.

#include "Widgets/InventoryGrid.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/InventoryComponent.h"

void UInventoryGrid::InitInventory(UInventoryComponent* GetInventoryComponent, float GetTileSize)
{
	InventoryComponent = GetInventoryComponent;
	TileSize = GetTileSize;

	auto GridBorderSize = FVector2D(InventoryComponent->Columns * TileSize, InventoryComponent->Rows * TileSize);
	UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryGrid_GridBorder)->SetSize(GridBorderSize);

	CreateSegments();
}

void UInventoryGrid::CreateSegments()
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