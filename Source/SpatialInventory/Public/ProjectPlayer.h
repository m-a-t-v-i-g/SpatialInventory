// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectPlayer.generated.h"

UCLASS()
class SPATIALINVENTORY_API AProjectPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AProjectPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
