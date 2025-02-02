// Spatial Inventory С++ template by matvig.

#include "Game/ProjectCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Game/Item/ItemBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/InventoryWidget.h"

AProjectCharacter::AProjectCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetMesh(), TEXT("head"));
	CameraComponent->bUsePawnControlRotation = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	PrimaryActorTick.bCanEverTick = true;
}

void AProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	auto CreateInventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryComponent->InventoryWidget);
	if (CreateInventoryWidget)
	{
		CreateInventoryWidget->InventoryComponent = InventoryComponent;
		CreateInventoryWidget->TileSize = TileSize;
		CreateInventoryWidget->InitInventoryWidget(InventoryComponent, TileSize);
		InventoryWidget = CreateInventoryWidget;
	}
}

void AProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindItem();
}

void AProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AProjectCharacter::PickUpItem);

		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this,
		                                   &AProjectCharacter::ToggleInventory);

		EnhancedInputComponent->BindAction(DebugInventoryAction, ETriggerEvent::Started, this,
								   &AProjectCharacter::DebugInventory);
	}
}

void AProjectCharacter::OnFind(bool bFind)
{
	IInteractInterface::OnFind(bFind);
}

void AProjectCharacter::OnPickUp(AActor* InteractedActor)
{
	IInteractInterface::OnPickUp(InteractedActor);
}

void AProjectCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectCharacter::ToggleInventory()
{
	if (!InventoryWidget) return;

	auto PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;

	if (InventoryWidget->IsInViewport())
	{
		InventoryWidget->RemoveFromParent();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->bShowMouseCursor = false;
	}
	else
	{
		InventoryWidget->AddToViewport();
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, InventoryWidget);
		PlayerController->bShowMouseCursor = true;
	}
}

void AProjectCharacter::FindItem()
{
	if (!GetWorld()) return;

	FHitResult HitResult;
	FVector ViewLocation;
	FRotator ViewRotation;

	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	auto TraceStart = ViewLocation;
	auto TraceEnd = ViewLocation + ViewRotation.Vector() * InteractDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	auto bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);
	if (bHit)
	{
		if (HitResult.GetActor()->IsA<AItemBase>())
		{
			FocusedActor = HitResult.GetActor();
			if (IInteractInterface* InteractInterface = Cast<IInteractInterface>(FocusedActor))
			{
				InteractInterface->OnFind(true);
				return;
			}
		}
	}
	if (IInteractInterface* InteractInterface = Cast<IInteractInterface>(FocusedActor))
	{
		InteractInterface->OnFind(false);
		FocusedActor = nullptr;
	}
}

void AProjectCharacter::PickUpItem()
{
	if (!GetWorld()) return;

	if (!FocusedActor) return;
	
	if (FocusedActor->IsA<AItemBase>())
	{
		if (IInteractInterface* InteractInterface = Cast<IInteractInterface>(FocusedActor))
		{
			InteractInterface->OnPickUp(this);
		}
	}
}

void AProjectCharacter::DebugInventory()
{
	if (!InventoryComponent) return;

	InventoryComponent->DebugInventory();
}