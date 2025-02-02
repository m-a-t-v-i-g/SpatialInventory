// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectGameState.generated.h"

class UItemObject;

UCLASS()
class SPATIALINVENTORY_API AProjectGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	void SpawnItemFromActor(UItemObject* ItemObject, AActor* OtherActor, bool GroundClamp);
};
