// Spatial Inventory С++ template by matvig.

#include "Game/Item/ItemBase.h"
#include "Game/ProjectCharacter.h"
#include "Game/Item/ItemObject.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"

AItemBase::AItemBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->CanCharacterStepUpOn = ECB_No;
	
	PrimaryActorTick.bCanEverTick = true;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	InitItem();
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::OnFind(bool bFind)
{
	if (!StaticMeshComponent) return;

	StaticMeshComponent->SetRenderCustomDepth(bFind);
}

void AItemBase::OnPickUp(AActor* InteractedActor)
{
	if (!InteractedActor) return;

	if (!StaticMeshComponent) return;
	
	StaticMeshComponent->SetRenderCustomDepth(false);

	auto GetPlayerPawn = Cast<AProjectCharacter>(InteractedActor);
	if (GetPlayerPawn)
	{
		auto GetInventory = GetPlayerPawn->GetInventoryComponent();
		if (!GetInventory) return;

		if (GetInventory->TryAddItem(ItemObject))
		{
			Destroy();
		}
	}
}

UItemObject* AItemBase::GetItemObject()
{
	const auto ConstructItemObject = NewObject<UItemObject>();
	if (ConstructItemObject)
	{
		ConstructItemObject->Dimensions = FIntPoint(Item.SizeX, Item.SizeY);
		ConstructItemObject->Icon = Item.Icon;
		ConstructItemObject->ItemClass = GetClass();
		return ItemObject = ConstructItemObject;
	}
	return nullptr;
}

void AItemBase::InitItem()
{
	if (!ItemObject)
	{
		GetItemObject();
	}
}
