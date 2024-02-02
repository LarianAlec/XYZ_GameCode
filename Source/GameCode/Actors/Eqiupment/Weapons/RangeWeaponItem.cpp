// Alec Larin


#include "RangeWeaponItem.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WeaponComponents/WeaponBarrelComponent.h"
#include "GameCodeTypes.h"
#include "Characters/GCBaseCharacter.h"

ARangeWeaponItem::ARangeWeaponItem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root"));
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponBarrel = CreateDefaultSubobject<UWeaponBarrelComponent>(TEXT("Weapon Barrel"));
	WeaponBarrel->SetupAttachment(WeaponMesh, SocketWeaponMuzzle);
}

void ARangeWeaponItem::Fire()
{
	checkf(GetOwner()->IsA<AGCBaseCharacter>(), TEXT("ARangeWeaponItem::Fire() only AGCBaseCharacter can be an owner of a ARangeWeaponItem"))
	AGCBaseCharacter* CharacterOwner = StaticCast<AGCBaseCharacter*>(GetOwner());

	APlayerController* Controller = CharacterOwner->GetController<APlayerController>();

	if (!IsValid(Controller))
	{
		return;
	}

	FVector PlayerViewPoint;
	FRotator PlayerViewRotation;

	Controller->GetPlayerViewPoint(PlayerViewPoint, PlayerViewRotation);

	FVector ViewDirection = PlayerViewRotation.RotateVector(FVector::ForwardVector);

	WeaponBarrel->Shot(PlayerViewPoint, ViewDirection, Controller);
}
