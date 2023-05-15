// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractInterface.h"
#include "InputActionValue.h"
#include "ProjectPlayer.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInventoryWidget;
class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryInit);

UCLASS()
class SPATIALINVENTORY_API AProjectPlayer : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	AProjectPlayer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DebugInventoryAction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	float TileSize = 50.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	float InteractDistance = 215.0;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnInteract(AActor* InteractedActor) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; };

	void ToggleInventory();

	void PickUpItem();

	// Debugging
	void DebugInventory();
};
