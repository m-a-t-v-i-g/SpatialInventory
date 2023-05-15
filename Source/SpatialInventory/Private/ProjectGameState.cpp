// Spatial Inventory С++ template by matvig.

#include "ProjectGameState.h"
#include "Base/ItemBase.h"
#include "Base/ItemObject.h"

void AProjectGameState::SpawnItemFromActor(UItemObject* ItemObject, AActor* OtherActor, bool GroundClamp)
{
	FHitResult HitResult;
	FVector SpawnLocation;
	
	SpawnLocation = FVector(OtherActor->GetActorLocation() + OtherActor->GetActorForwardVector() * 150.0);

	if (GroundClamp)
	{
		auto bHit = GetWorld()->LineTraceSingleByChannel(HitResult, SpawnLocation,
												 SpawnLocation - FVector(0.0, 0.0, 1000.0), ECC_Visibility);
		if (bHit)
		{
			SpawnLocation = HitResult.Location;
		}
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	auto SpawnItem = GetWorld()->SpawnActor<AItemBase>(ItemObject->GetItemClass(), SpawnLocation, FRotator(0.0,0.0,0.0), SpawnParams);
	if (SpawnItem)
	{
		SpawnItem->ItemObject = ItemObject;
	}
}
