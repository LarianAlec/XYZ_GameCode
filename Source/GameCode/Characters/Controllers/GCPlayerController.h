// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GCPlayerController.generated.h"

struct FInputActionValue;
class UPlayerHudWidget;
UCLASS()
class GAMECODE_API AGCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced input")
	class UGCCharacterInputConfigData* InputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Widgets")
	TSubclassOf<UPlayerHudWidget> PlayerHudWidgetClass;

	virtual void SetupInputComponent() override;
	
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void PlayerStartFire(const FInputActionValue& Value);
	void PlayerStopFire(const FInputActionValue& Value);
	void StartAiming(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);

	TSoftObjectPtr<class AGCBaseCharacter> CachedBaseCharacter;

	void CreateAndInitializeWidgets();

	UPlayerHudWidget* PlayerHudWidget = nullptr;
};
