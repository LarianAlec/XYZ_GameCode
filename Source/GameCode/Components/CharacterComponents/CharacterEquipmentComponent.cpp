// Alec Larin


#include "CharacterEquipmentComponent.h"
#include "Characters/GCBaseCharacter.h"
#include "Actors/Eqiupment/Weapons/RangeWeaponItem.h"
#include "GameCodeTypes.h"


EEquipableItemType UCharacterEquipmentComponent::GetCurrentEquippedItemType() const 
{
	EEquipableItemType Result = EEquipableItemType::None;
	if (IsValid(CurrentEquippedWeapon))
	{
		Result = CurrentEquippedWeapon->GetItemType();
	}
	return Result;
}

ARangeWeaponItem* UCharacterEquipmentComponent::GetCurrentRangeWeapon() const
{
	return CurrentEquippedWeapon;
}


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
	CurrentEquippedWeapon = GetWorld()->SpawnActor<ARangeWeaponItem>(SideArmClass);
	CurrentEquippedWeapon->AttachToComponent(CachedBaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketCharacterWeapon);
	CurrentEquippedWeapon->SetOwner(CachedBaseCharacter.Get());
}
