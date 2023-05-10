// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "ProjectTypes.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

class UCanvasPanel;
class UBorder;
class UInventoryComponent;

UCLASS()
class SPATIALINVENTORY_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryGrid_MainPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> InventoryGrid_GridBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryGrid_GridPanel;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	float TileSize = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TArray<FLine> Lines;
	
public:
	void InitInventory(UInventoryComponent* GetInventoryComponent, float GetTileSize);

private:
	void CreateSegments();

protected:
	static FLine MakeLineX(FLine& line, float x, float tile_size)
	{
		line.Start = FVector2D(x, 0.0);
		line.End = FVector2D(x, tile_size);
		return line;
	}
	
	static FLine MakeLineY(FLine& line, float y, float tile_size)
	{
		line.Start = FVector2D(0, y);
		line.End = FVector2D(tile_size, y);
		return line;
	}
	
};

