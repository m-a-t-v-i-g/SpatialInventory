// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "ProjectTypes.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryWidget;
class UInventoryGridWidget;
class UInventoryItemWidget;
class USlateBrushAsset;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPATIALINVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Size")
	int Columns = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Size")
	int Rows = 1;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Inventory")
	FTile Tile;

	UPROPERTY(VisibleDefaultsOnly, Category = "Inventory")
	TArray<UItemObject*> Inventory;

public:
	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UInventoryWidget> InventoryWidget;

	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UInventoryGridWidget> InventoryGridWidget;
	
	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UInventoryItemWidget> InventoryItemWidget;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USlateBrushAsset> SlateBrushColor;

protected:
	// Called only on begin play
	void InitInventory();

public:
	FOnInventoryChanged OnInventoryChanged;

	// For add item to inventory
	bool TryAddItem(UItemObject* ItemToAdd);
	bool IsRoomAvailable(UItemObject* ItemObject, int TopLeftIndex);
	UItemObject* GetItemAtIndex(int Index);
	void AddItemAt(UItemObject* ItemObject, int TopLeftIndex);

	// Get items at inventory by tile
	TMap<UItemObject*, FTile> GetAllItems();

	// Remove item from inventory
	UFUNCTION()
	void RemoveItem(UItemObject* ItemObject);
	
	static FTile IndexToTile(FTile& tile, int32 index, int32 size)
	{
		tile.X = index % size;
		tile.Y = index / size;
		return tile;
	}
	
	static int TileToIndex(int32 index_x, int32 index_y, int32 size)
	{
		return index_x + index_y * size;
	}
	
	// Debugging
	void DebugInventory();
};
