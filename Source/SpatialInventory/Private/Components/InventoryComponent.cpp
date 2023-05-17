// Spatial Inventory С++ template by matvig.

#include "Components/InventoryComponent.h"
#include "Game/Item/ItemObject.h"
#include "Slate/SlateBrushAsset.h"
#include "Widgets/InventoryItemWidget.h"

UInventoryComponent::UInventoryComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WB_InventoryWidget(TEXT("/Game/Widgets/WB_Inventory"));
	InventoryWidget = WB_InventoryWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_InventoryGridWidget(TEXT("/Game/Widgets/WB_InventoryGrid"));
	InventoryGridWidget = WB_InventoryGridWidget.Class;
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WB_InventoryItemWidget(TEXT("/Game/Widgets/WB_InventoryItem"));
	InventoryItemWidget = WB_InventoryItemWidget.Class;

	static ConstructorHelpers::FObjectFinder<USlateBrushAsset> SB_Color(TEXT("/Game/Widgets/SB_Color"));
	SlateBrushColor = SB_Color.Object;
	
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

	auto ItemWidget = Cast<UInventoryItemWidget>(InventoryItemWidget);
	if (ItemWidget)
	{
		ItemWidget->OnRemoved.AddDynamic(this, &UInventoryComponent::RemoveItem);
	}
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
			OnInventoryChanged.Broadcast();
		}
	}
}

TMap<UItemObject*, FTile> UInventoryComponent::GetAllItems()
{
	TMap<UItemObject*, FTile> AllItems;
	
	for (int i = 0; i < Inventory.Num(); i++)
	{
		auto CurrentItemObject = Inventory[i];
		if (IsValid(CurrentItemObject))
		{
			if (!AllItems.Contains(Inventory[i]))
			{
				AllItems.Add(Inventory[i], IndexToTile(Tile, i, Columns));
			}
		}
	}
	return AllItems;
}

void UInventoryComponent::RemoveItem(UItemObject* ItemObject)
{
	if (ItemObject)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			if (Inventory[i] == ItemObject)
			{
				Inventory[i] = nullptr;
				OnInventoryChanged.Broadcast();
			}
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
