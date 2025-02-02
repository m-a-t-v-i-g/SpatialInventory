// Spatial Inventory С++ template by matvig.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectTypes.generated.h"

class AItemBase;

USTRUCT(BlueprintType, Blueprintable)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Start = FVector2D(0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D End = FVector2D(0.0f, 0.0f);
};

USTRUCT(BlueprintType, Blueprintable)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y = 1;
};

USTRUCT(BlueprintType, Blueprintable)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icon")
	TObjectPtr<UMaterialInterface> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icon")
	int SizeX = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icon")
	int SizeY = 1;

};

UCLASS()
class SPATIALINVENTORY_API UProjectTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
