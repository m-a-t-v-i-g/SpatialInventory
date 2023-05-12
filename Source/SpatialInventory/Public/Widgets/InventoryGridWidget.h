// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "ProjectTypes.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UInventoryComponent;
class UInventoryItemWidget;
class UItemObject;

UCLASS()
class SPATIALINVENTORY_API UInventoryGridWidget : public UUserWidget
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
	TArray<FLine> Lines;

public:
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	float TileSize = 0.0f;

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void InitInventory(UInventoryComponent* GetInventoryComponent, float GetTileSize);

private:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	                          const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	                          const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void CreateSegments();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void Refresh();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void OnItemRemoved(UItemObject* ItemObject);

protected:
	static FLine MakeLineX(FLine& line, float x, float tile_size)
	{
		line.Start = FVector2D(x, 0);
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

