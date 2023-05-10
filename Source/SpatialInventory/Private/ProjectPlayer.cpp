// Spatial Inventory С++ template by matvig.

#include "ProjectPlayer.h"
#include "Components/InventoryComponent.h"

AProjectPlayer::AProjectPlayer()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	
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
