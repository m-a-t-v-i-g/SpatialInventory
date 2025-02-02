// Spatial Inventory С++ template by matvig.

#include "Game/ProjectGameState.h"
#include "Game/Item/ItemBase.h"
#include "Game/Item/ItemObject.h"
#include "Kismet/KismetMathLibrary.h"

void AProjectGameState::SpawnItemFromActor(UItemObject* ItemObject, AActor* OtherActor, bool GroundClamp)
{
	FHitResult HitResult;
	FVector SpawnLocation;
	FRotator SpawnRotation = GroundClamp
		                         ? OtherActor->GetActorRotation() + FRotator(0.0, 90.0, -90.0)
		                         : OtherActor->GetActorRotation() + FRotator(UKismetMathLibrary::RandomFloatInRange(-180.0, 180.0), 90.0, 0.0);

	float SpawnDistance = GroundClamp ? 100.0 : 65.0;

	SpawnLocation = FVector(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z + 40.0) + OtherActor->GetActorForwardVector() * SpawnDistance;
	
	// If true, item spawns on ground without physic simulation
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

	auto SpawnItem = GetWorld()->SpawnActor<AItemBase>(ItemObject->GetItemClass(), SpawnLocation, SpawnRotation, SpawnParams);
	if (SpawnItem)
	{
		SpawnItem->ItemObject = ItemObject;
		if (!GroundClamp)
		{
			SpawnItem->GetStaticMesh()->AddImpulse(OtherActor->GetActorForwardVector() * 1000.0);
			SpawnItem->GetStaticMesh()->AddAngularImpulseInDegrees(FVector(UKismetMathLibrary::RandomFloatInRange(-180.0, 180.0)));
		}
	}
}
