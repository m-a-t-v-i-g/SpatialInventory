// Spatial Inventory С++ template by matvig.


#include "Game/ProjectGameMode.h"
#include "Game/ProjectGameState.h"
#include "Game/ProjectHUD.h"

AProjectGameMode::AProjectGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> BP_Character(TEXT("/Game/Game/Player/BP_Character"));
	if (BP_Character.Class != nullptr)
	{
		DefaultPawnClass = BP_Character.Class;
	}

	HUDClass = AProjectHUD::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APlayerController> BP_PlayerController(TEXT("/Game/Game/Player/BP_PlayerController"));
	if (BP_PlayerController.Class != nullptr)
	{
		PlayerControllerClass = BP_PlayerController.Class;
	}

	GameStateClass = AProjectGameState::StaticClass();
}
