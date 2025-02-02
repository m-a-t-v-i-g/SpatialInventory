// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class SPATIALINVENTORY_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void OnFind(bool bFind);
	
	virtual void OnPickUp(AActor* InteractedActor);
};
