// Alec Larin

#include "GCBaseCharacter.h"
#include "../Components/Character/CharacterAttributesComponent.h"

AGCBaseCharacter::AGCBaseCharacter()
{
	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character Attributes"));
}
