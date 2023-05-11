// Spatial Inventory С++ template by matvig.

#include "Components/InventoryComponent.h"

#include "Base/ItemObject.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitInventory();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UInventoryComponent::InitInventory()
{
	int InventorySize = Columns * Rows;
	Inventory.SetNum(InventorySize);
	
	DebugInventory();
}

bool UInventoryComponent::TryAddItem(UItemObject* ItemToAdd)
{
	if (!IsValid(ItemToAdd)) return false;
	
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		if (IsRoomAvailable(ItemToAdd, i))
		{
			AddItemAt(ItemToAdd, i);
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::IsRoomAvailable(UItemObject* ItemObject, int TopLeftIndex)
{
	int IndexToTileX = IndexToTile(Tile, TopLeftIndex, Columns).X;
	int IndexToTileY = IndexToTile(Tile, TopLeftIndex, Columns).Y;

	int TileDimensionAmountX = IndexToTileX + (ItemObject->GetDimensions().X - 1);
	int TileDimensionAmountY = IndexToTileY + (ItemObject->GetDimensions().Y - 1);
	
	for (int x = IndexToTileX; x <= TileDimensionAmountX; ++x)
	{
		for (int y = IndexToTileY; y <= TileDimensionAmountY; ++y)
		{
			if(x >= 0 && y >= 0 && x < Columns && y < Rows)
			{
				if (IsValid(GetItemAtIndex(TileToIndex(x, y, Columns))))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

UItemObject* UInventoryComponent::GetItemAtIndex(int Index)
{
	if (Inventory.IsValidIndex(Index))
	{
		return Inventory[Index];
	}
	return nullptr;
}

void UInventoryComponent::AddItemAt(UItemObject* ItemObject, int TopLeftIndex)
{
	int IndexToTileX = IndexToTile(Tile, TopLeftIndex, Columns).X;
	int IndexToTileY = IndexToTile(Tile, TopLeftIndex, Columns).Y;

	int TileDimensionAmountX = IndexToTileX + (ItemObject->GetDimensions().X - 1);
	int TileDimensionAmountY = IndexToTileY + (ItemObject->GetDimensions().Y - 1);
	
	for (int x = IndexToTileX; x <= TileDimensionAmountX; ++x)
	{
		for (int y = IndexToTileY; y <= TileDimensionAmountY; ++y)
		{
			Inventory[TileToIndex(x, y, Columns)] = ItemObject;
		}
	}
}

void UInventoryComponent::DebugInventory()
{
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		if (IsValid(Inventory[i]))
		{
			UE_LOG(LogTemp, Warning, TEXT("%d, %s"), i, *Inventory[i]->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%d, %s"), i, *Inventory[i]->GetFullName());
		}
	}
}
