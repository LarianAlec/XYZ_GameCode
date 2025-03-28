// Alec Larin


#include "GCBaseCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/GCBaseCharacter.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"
#include "Actors/Eqiupment/Weapons/RangeWeaponItem.h"

void UGCBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<AGCBaseCharacter>(), TEXT("UGCBaseCharacterAnimInstance::NativeBeginPlay() UGCBaseCharacterAnimInstance must be used only with AGCBaseCharacter"));
	CachedBaseCharacter = StaticCast<AGCBaseCharacter*>(TryGetPawnOwner());
}

void UGCBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	bIsAiming = CachedBaseCharacter->IsAiming();

	UCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetCharacterMovement();
	Speed = CharacterMovement->Velocity.Size();
	bIsFalling = CharacterMovement->IsFalling();
	
	bIsStrafing = !CharacterMovement->bOrientRotationToMovement;
	Direction = CalculateDirection(CharacterMovement->Velocity, CachedBaseCharacter->GetActorRotation());

	AimRotation = CachedBaseCharacter->GetBaseAimRotation();

	const UCharacterEquipmentComponent* CharacterEquipment = CachedBaseCharacter->GetCharacterEquipmentComponent();
	CurrentEquippedItemType = CharacterEquipment->GetCurrentEquippedItemType();

	ARangeWeaponItem* CurrentRangeWeapon = CharacterEquipment->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		ForeGripSocketTransform = CurrentRangeWeapon->GetForeGripTransform();
	}
}