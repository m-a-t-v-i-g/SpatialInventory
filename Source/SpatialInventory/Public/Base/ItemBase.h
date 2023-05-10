// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class SPATIALINVENTORY_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
