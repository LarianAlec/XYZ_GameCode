// Alec Larin


#include "AI/Characters/GCAICharacter.h"
#include "Components/CharacterComponents/AIPatrollingComponent.h"

AGCAICharacter::AGCAICharacter()
{
	AIPatrollingComponent = CreateDefaultSubobject<UAIPatrollingComponent>(TEXT("AIPatrolling"));
}

UAIPatrollingComponent* AGCAICharacter::GetPatrollingComponent() const
{
	return AIPatrollingComponent;
}
