// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "ProjectTypes.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryWidget;
class UInventoryGridWidget;
class UInventoryItemWidget;
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
	
	FTile Tile;

	TArray<UItemObject*> Inventory;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Size")
	int Columns = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory Size")
	int Rows = 1;

protected:
	void InitInventory();

public:
	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UInventoryWidget> InventoryWidget;

	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UInventoryGridWidget> InventoryGridWidget;
	
	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UInventoryItemWidget> InventoryItemWidget;
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;
	
	bool TryAddItem(UItemObject* ItemToAdd);
	bool IsRoomAvailable(UItemObject* ItemObject, int TopLeftIndex);
	UItemObject* GetItemAtIndex(int Index);
	void AddItemAt(UItemObject* ItemObject, int TopLeftIndex);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
	TMap<UItemObject*, FTile> GetAllItems();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void RemoveItem(UItemObject* ItemObject);
	
private:
	// Convert an index of inventory array to inventory tile
	static FTile IndexToTile(FTile& tile, int32 index, int32 size)
	{
		tile.X = index % size;
		tile.Y = index / size;
		return tile;
	}
	// Convert tile of inventory to the index
	static int TileToIndex(int32 index_x, int32 index_y, int32 size)
	{
		return index_x + index_y * size;
	}

public:
	void DebugInventory();
	
};
