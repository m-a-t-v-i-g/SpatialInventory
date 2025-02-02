// Spatial Inventory С++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectHUD.generated.h"

UCLASS()
class SPATIALINVENTORY_API AProjectHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void DrawHUD() override;

public:
	void DrawCrosshair();
};
