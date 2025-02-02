// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

class AItemBase;

UCLASS()
class SPATIALINVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	FIntPoint Dimensions = FIntPoint(1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	TObjectPtr<UMaterialInterface> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	TSubclassOf<AItemBase> ItemClass;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FIntPoint GetDimensions() { return Dimensions; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UMaterialInterface* GetIcon() { return Icon; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<AItemBase> GetItemClass() { return ItemClass; }
};
