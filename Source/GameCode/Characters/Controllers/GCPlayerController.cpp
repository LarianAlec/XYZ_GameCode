// Alec Larin


#include "GCPlayerController.h"
#include "Characters/GCBaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Input/GCCharacterInputConfigData.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/PlayerHudWidget.h"
#include "UI/Widget/ReticleWidget.h"
#include "UI/Widget/AmmoWidget.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"


void AGCPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<AGCBaseCharacter>(InPawn);
	CreateAndInitializeWidgets();
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
			EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Look);
			EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Started, this, &AGCPlayerController::Jump);
			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Started, this, &AGCPlayerController::PlayerStartFire);
			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Completed, this, &AGCPlayerController::PlayerStopFire);
			EnhancedInputComponent->BindAction(InputActions->AimAction, ETriggerEvent::Started, this, &AGCPlayerController::StartAiming);
			EnhancedInputComponent->BindAction(InputActions->AimAction, ETriggerEvent::Completed , this, &AGCPlayerController::StopAiming);
			EnhancedInputComponent->BindAction(InputActions->ReloadAction, ETriggerEvent::Started, this, &AGCPlayerController::Reload);
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

void AGCPlayerController::PlayerStartFire(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartFire();
	}
}

void AGCPlayerController::PlayerStopFire(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopFire();
	}
}

void AGCPlayerController::StartAiming(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartAiming();
	}
}

void AGCPlayerController::StopAiming(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopAiming();
	}
}

void AGCPlayerController::Reload(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Reload();
	}
}

void AGCPlayerController::CreateAndInitializeWidgets()
{
	if (!IsValid(PlayerHudWidget))
	{
		PlayerHudWidget = CreateWidget<UPlayerHudWidget>(GetWorld(), PlayerHudWidgetClass);
		if (IsValid(PlayerHudWidget))
		{
			PlayerHudWidget->AddToViewport();
		}
	}
	
	if (IsValid(PlayerHudWidget) && CachedBaseCharacter.IsValid())
	{
		UReticleWidget* ReticleWidget = PlayerHudWidget->GetReticleWidget();
		if (IsValid(ReticleWidget))
		{
			CachedBaseCharacter->OnAimingStateChanged.AddUFunction(ReticleWidget, FName("OnAimingStateChanged"));
		}

		UAmmoWidget* AmmoWidget = PlayerHudWidget->GetAmmoWidget();
		if (IsValid(AmmoWidget))
		{
			UCharacterEquipmentComponent* CharacterEquipment = CachedBaseCharacter->GetCharacterEquipmentComponent_Mutable();
			CharacterEquipment->OnCurrentWeaponAmmoChangedEvent.AddUFunction(AmmoWidget, FName("UpdateAmmoCount"));
		}
	}
}
