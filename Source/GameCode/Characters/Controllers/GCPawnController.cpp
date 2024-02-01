// Alec Larin


#include "GCPawnController.h"
#include "../GameCodeBasePawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../../Input/GCCharacterInputConfigData.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

void AGCPawnController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBasePawn = Cast<AGameCodeBasePawn>(InPawn);
}

void AGCPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			checkf(IsValid(InputMapping), TEXT("AAGCPawnController::SetupInputComponent() Invalid InputMapping property!"));
			checkf(IsValid(InputActions), TEXT("AGCPawnController::SetupInputComponent() Invalid InputActions property!"));

			Subsystem->AddMappingContext(InputMapping, 0);

			UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
			EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &AGCPawnController::Move);
			EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Completed, this, &AGCPawnController::StopMoving);
			EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &AGCPawnController::Look);
			EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Started, this, &AGCPawnController::Jump);
		}
	}
}

void AGCPawnController::Move(const FInputActionValue& Value)
{
	if (CachedBasePawn.IsValid()) 
	{
		CachedBasePawn->Move(Value);
	}
}

void AGCPawnController::StopMoving(const FInputActionValue& Value)
{
	if (CachedBasePawn.IsValid())
	{
		CachedBasePawn->StopMoving(Value);
	}
}

void AGCPawnController::Look(const FInputActionValue& Value)
{
	if (CachedBasePawn.IsValid())
	{
		CachedBasePawn->Look(Value);
	}
}

void AGCPawnController::Jump(const FInputActionValue& Value)
{
	if (CachedBasePawn.IsValid())
	{
		CachedBasePawn->Jump(Value);
	}
}

