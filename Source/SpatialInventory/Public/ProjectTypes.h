// Spatial Inventory С++ template by matvig.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectTypes.generated.h"

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

UCLASS()
class SPATIALINVENTORY_API UProjectTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
