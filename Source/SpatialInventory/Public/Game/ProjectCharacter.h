// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractInterface.h"
#include "InputActionValue.h"
#include "ProjectCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInventoryWidget;
class UInventoryComponent;

UCLASS()
class SPATIALINVENTORY_API AProjectCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	AProjectCharacter();

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
	float TileSize = 60.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	float InteractDistance = 215.0;

	TObjectPtr<AActor> FocusedActor;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnFind(bool bFind) override;
	
	virtual void OnPickUp(AActor* InteractedActor) override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	
	void ToggleInventory();
	void FindItem();
	void PickUpItem();

	// Debugging
	void DebugInventory();
};
