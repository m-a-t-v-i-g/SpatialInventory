// Spatial Inventory С++ template by matvig.

#include "Base/ItemBase.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

