#pragma once

#include "../../../../../../../Source/Runtime/Core/Public/UObject/NameTypes.h"

#define ECC_Bullet ECC_GameTraceChannel1

const FName SocketCharacterWeapon = FName("CharacterWeaponSocket");
const FName SocketWeaponMuzzle = FName("MuzzleSocket");
const FName DebugCategoryRangeWeapon = FName("RangeWeapon");

UENUM(BlueprintType)
enum class EEquipableItemType : uint8
{
	None, 
	Pistol
};
