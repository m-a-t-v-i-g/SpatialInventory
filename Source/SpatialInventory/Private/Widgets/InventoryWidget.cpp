// Spatial Inventory С++ template by matvig.

#include "Widgets/InventoryWidget.h"
#include "Game/ProjectGameState.h"
#include "Game/Item/ItemObject.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Border.h"
#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!Inventory_BackgroundBorder) return;
	Inventory_BackgroundBorder->OnMouseButtonDownEvent.BindDynamic(this, &UInventoryWidget::HandleMouseButtonDown);
}

void UInventoryWidget::InitInventoryWidget(UInventoryComponent* SetInventoryComponent, float SetTileSize)
{
	InventoryComponent = SetInventoryComponent;
	TileSize = SetTileSize;

	if (!InventoryComponent) return;

	Inventory_InventoryGridWidget->InitInventory(InventoryComponent, TileSize);
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                    UDragDropOperation* InOperation)
{
	auto GetGameState = Cast<AProjectGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GetGameState)
	{
		auto Payload = Cast<UItemObject>(InOperation->Payload);
		GetGameState->SpawnItemFromActor(Payload, InventoryComponent->GetOwner(), false);
		return true;
	}
	return false;
}

FEventReply UInventoryWidget::HandleMouseButtonDown(FGeometry InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply EventReply = FEventReply(true);
	return EventReply;
}