// Spatial Inventory С++ template by matvig.

#include "Base/ItemBase.h"
#include "ProjectPlayer.h"
#include "Base/ItemObject.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"

AItemBase::AItemBase()
{
	RootComponent = SphereComponent;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(RootComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SphereComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(SphereComponent);
	
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

void AItemBase::OnInteract(AActor* InteractedActor)
{
	if (!InteractedActor) return;
	
	auto GetPlayerPawn = Cast<AProjectPlayer>(InteractedActor);
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
		ConstructItemObject->ItemClass = Item.ItemClass;
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
