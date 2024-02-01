// Alec Larin


#include "RangeWeaponItem.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WeaponComponents/WeaponBarrelComponent.h"
#include "GameCodeTypes.h"

ARangeWeaponItem::ARangeWeaponItem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root"));
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponBarrel = CreateDefaultSubobject<UWeaponBarrelComponent>(TEXT("Weapon Barrel"));
	WeaponBarrel->SetupAttachment(WeaponMesh, SocketWeaponMuzzle);
}