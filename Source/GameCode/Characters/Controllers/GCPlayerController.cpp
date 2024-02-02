// Alec Larin


#include "GCPlayerController.h"
#include "Characters/GCBaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Input/GCCharacterInputConfigData.h"
#include "InputMappingContext.h"


void AGCPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<AGCBaseCharacter>(InPawn);
}

void AGCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			checkf(IsValid(InputMapping), TEXT("AGCPlayerController::SetupInputComponent InputMapping must be valid!"));
			checkf(IsValid(InputActions), TEXT("AGCPlayerController::SetupInputComponent InputActions must be valid!"));

			Subsystem->AddMappingContext(InputMapping, 0);

			UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
			EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Move);
			//EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Completed, this, &AGCPlayerController::StopMoving);
			EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Look);
			EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Started, this, &AGCPlayerController::Jump);
			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Started, this, &AGCPlayerController::Fire);
		}
	}
}

void AGCPlayerController::Move(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		CachedBaseCharacter->MoveForward(MovementVector.Y);
		CachedBaseCharacter->MoveRight(MovementVector.X);
	}
}

/*
void AGCPlayerController::StopMoving(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		//CachedBaseCharacter->StopMoving(Value);
	}
}
*/

void AGCPlayerController::Look(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		const FVector2D LookVector = Value.Get<FVector2D>();
		CachedBaseCharacter->LookUp(LookVector.Y);
		CachedBaseCharacter->Turn(LookVector.X);
	}
}

void AGCPlayerController::Jump(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}

void AGCPlayerController::Fire(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Fire();
	}
}
