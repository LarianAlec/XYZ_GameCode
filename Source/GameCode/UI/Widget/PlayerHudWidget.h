// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHudWidget.generated.h"


UCLASS()
class GAMECODE_API UPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UReticleWidget* GetReticleWidget();

	class UAmmoWidget* GetAmmoWidget();

protected:
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget names")
	FName ReticleWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget names")
	FName AmmoWidgetName;
};
