// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

class USizeBox;
class UBorder;
class UImage;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoved, class UItemObject*, ItemObject);

UCLASS()
class SPATIALINVENTORY_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> Item_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> Item_Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Item_Image;
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UItemObject> ItemObject;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FVector2D Size;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.0;

private:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnInitialized() override;

public:
	// Called when item removed from inventory widget
	FOnRemoved OnRemoved;
	
	// Get icon from current item object
	UFUNCTION()
	FSlateBrush GetItemIcon();
	
	// Refresh item in inventory widget
	void Refresh();
};
