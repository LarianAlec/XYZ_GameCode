// Alec Larin


#include "PlayerHudWidget.h"
#include "GameFramework/Pawn.h"
#include "Characters/GCBaseCharacter.h"
#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "ReticleWidget.h"
#include "Blueprint/WidgetTree.h"

float UPlayerHudWidget::GetHealthPercent() const
{
	float Result = 1.0f;
	APawn* Pawn = GetOwningPlayerPawn();
	AGCBaseCharacter* Character = Cast<AGCBaseCharacter>(Pawn);
	if (IsValid(Character))
	{
		const UCharacterAttributesComponent* CharacterAttributes = Character->GetCharacterAttributesComponent();
		Result = CharacterAttributes->GetHealthPercent();
	}
	return Result;
}

UReticleWidget* UPlayerHudWidget::GetReticleWidget()
{
	return WidgetTree->FindWidget<UReticleWidget>(ReticleWidgetName);
}