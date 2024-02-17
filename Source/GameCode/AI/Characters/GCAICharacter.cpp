// Alec Larin


#include "AI/Characters/GCAICharacter.h"
#include "Components/CharacterComponents/AIPatrollingComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AGCAICharacter::AGCAICharacter()
{
	AIPatrollingComponent = CreateDefaultSubobject<UAIPatrollingComponent>(TEXT("AIPatrolling"));
}

UAIPatrollingComponent* AGCAICharacter::GetPatrollingComponent() const
{
	return AIPatrollingComponent;
}

UBehaviorTree* AGCAICharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}
