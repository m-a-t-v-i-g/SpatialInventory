// Spatial Inventory С++ template by matvig.

#include "ProjectPlayer.h"

AProjectPlayer::AProjectPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AProjectPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
