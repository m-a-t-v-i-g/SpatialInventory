// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UBackgroundBlur;
class UInventoryGridWidget;
class UInventoryComponent;

UCLASS()
class SPATIALINVENTORY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Inventory_MainPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> Inventory_BackgroundPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> Inventory_BackgroundBlur;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventoryGridWidget> Inventory_InventoryGridWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (ExposeOnSpawn = "true"))
	float TileSize = 0.0f;

};
