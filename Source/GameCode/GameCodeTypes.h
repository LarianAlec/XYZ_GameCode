#pragma once

#include "../../../../../../../Source/Runtime/Core/Public/UObject/NameTypes.h"

#define ECC_Bullet ECC_GameTraceChannel1

const FName FXParamTraceEnd = FName("TraceEnd");

const FName SocketCharacterWeapon = FName("CharacterWeaponSocket");
const FName SocketWeaponMuzzle = FName("MuzzleSocket");
const FName SocketWeaponForeGrip = FName("ForeGripSocket");

const FName DebugCategoryRangeWeapon = FName("RangeWeapon");

const FName BB_CurrentTarget = FName("CurrentTurget");
const FName BB_NextLocation = FName("NextLocation");

UENUM(BlueprintType)
enum class EEquipableItemType : uint8
{
	None, 
	Pistol,
	Rifle
};

UENUM(BlueprintType)
enum class EAmunitionType : uint8
{
	None,
	Pistol,
	Rifle,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EEquipmentSlots : uint8
{
	None,
	SideArm,
	PrimeryWeapon,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ETeams : uint8
{
	Player,
	Enemy
};