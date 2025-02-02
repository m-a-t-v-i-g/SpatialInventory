// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "ProjectTypes.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "ItemBase.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;
class UItemObject;

UCLASS()
class SPATIALINVENTORY_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	AItemBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FItem Item;

public:
	virtual void Tick(float DeltaTime) override;

	void OnFind(bool bFind) override;
	
	void OnPickUp(AActor* InteractedActor) override;

	virtual UItemObject* GetItemObject();

	UPROPERTY(VisibleDefaultsOnly, Category = "Inventory")
	TObjectPtr<UItemObject> ItemObject;

	UStaticMeshComponent* GetStaticMesh() { return StaticMeshComponent; };

protected:
	void InitItem();
};
