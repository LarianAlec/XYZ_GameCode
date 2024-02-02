#pragma once
#include "../../../../../../../Source/Runtime/Core/Public/UObject/NameTypes.h"

const FName SocketCharacterWeapon = FName("CharacterWeaponSocket");
const FName SocketWeaponMuzzle = FName("MuzzleSocket");

UENUM(BlueprintType)
enum class EEquipableItemType : uint8
{
	None, 
	Pistol
};
