// Spatial Inventory С++ template by matvig.

#include "Interfaces/InteractInterface.h"

void IInteractInterface::OnInteract()
{
	GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Red, TEXT("Interact"));
}