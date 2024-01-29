// Alec Larin


#include "GameCodePlayerController.h"
#include "EnhancedInputSubsystems.h"

void AGameCodePlayerController::BeginPlay() 
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(this)) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}