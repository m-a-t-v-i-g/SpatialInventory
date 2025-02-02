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
	virtual void NativePreConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryGrid_MainPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> InventoryGrid_GridBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InventoryGrid_GridPanel;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.0f;

protected:
	TArray<FLine> Lines;

public:
	// Called only on begin play
	UFUNCTION(BlueprintCallable)
	void InitInventory(UInventoryComponent* SetInventoryComponent, float SetTileSize);

private:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
							  const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
							  const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	// When item is dragging
	FIntPoint DraggedItemTopLeftTile;
	bool bDrawDropLocation = false;

	// Draw inventory segments
	void CreateSegments();

	// For Drag and Drop
	UItemObject* GetPayload(UDragDropOperation* InOperation) const;
	bool IsRoomAvailableForPayload(UItemObject* Payload) const;

	// Remove item from inventory widget
	UFUNCTION()
	void OnItemRemoved(UItemObject* ItemObject);

	// Lock mouse button when clicking in screen space
	UFUNCTION()
	FEventReply HandleMouseButtonDown(FGeometry InGeometry, const FPointerEvent& InMouseEvent);

public:
	// Refresh inventory widget
	UFUNCTION()
	void Refresh();
	
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

	static bool MouseTilePositionX(float mouse_positionX, float tile_size)
	{
		if (FGenericPlatformMath::Fmod(mouse_positionX, tile_size) > tile_size / 2.0)
		{
			return true;
		}
		return false;
	}

	static bool MouseTilePositionY(float mouse_positionY, float tile_size)
	{
		if (FGenericPlatformMath::Fmod(mouse_positionY, tile_size) > tile_size / 2.0)
		{
			return true;
		}
		return false;
	}
};

