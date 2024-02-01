// Alec Larin


#include "CharacterEquipmentComponent.h"
#include "Characters/GCBaseCharacter.h"
#include "Actors/Eqiupment/Weapons/RangeWeaponItem.h"
#include "GameCodeTypes.h"


void UCharacterEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(GetOwner()->IsA<AGCBaseCharacter>(), TEXT(" UCharacterEquipmentComponent::BeginPlay() can be used only with AGCBaseCharacter"));
	CachedBaseCharacter = StaticCast<AGCBaseCharacter*>(GetOwner());
	CreateLoadout();
}

void UCharacterEquipmentComponent::CreateLoadout()
{
	if (!IsValid(SideArmClass))
	{
		return;
	}
	CurrentEquipedItem = GetWorld()->SpawnActor<ARangeWeaponItem>(SideArmClass);
	CurrentEquipedItem->AttachToComponent(CachedBaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketCharacterWeapon);
}
