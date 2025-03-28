// Alec Larin

#include "GCBaseCharacter.h"
#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/HitResult.h"
#include "GameFramework/Actor.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"
#include "Actors/Eqiupment/Weapons/RangeWeaponItem.h"
#include "AIController.h"


AGCBaseCharacter::AGCBaseCharacter()
{
	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character Attributes"));
	CharacterEquipmentComponent = CreateDefaultSubobject<UCharacterEquipmentComponent>(TEXT("Character Equipment"));
	MaxMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AGCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributesComponent->OnDeathEvent.AddUObject(this, &AGCBaseCharacter::OnDeath);
}

void AGCBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AAIController* AIController = Cast<AAIController>(NewController);
	if (IsValid(AIController))
	{
		FGenericTeamId TeamId((uint8)Team);
		AIController->SetGenericTeamId(TeamId);
	}
}

void AGCBaseCharacter::StartFire()
{
	if (CharacterEquipmentComponent->IsEquipping())
	{
		return;
	}
	ARangeWeaponItem* CurrentRangeWeapon = CharacterEquipmentComponent->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		CurrentRangeWeapon->StartFire();
	}
}

void AGCBaseCharacter::StopFire()
{
	ARangeWeaponItem* CurrentRangeWeapon = CharacterEquipmentComponent->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		CurrentRangeWeapon->StopFire();
	}
}

void AGCBaseCharacter::StartAiming()
{
	ARangeWeaponItem* CurrentRangeWeapon = GetCharacterEquipmentComponent()->GetCurrentRangeWeapon();
	if (!IsValid(CurrentRangeWeapon))
	{
		return;
	}

	bIsAiming = true;
	CurrentAimingMovementSpeed = CurrentRangeWeapon->GetAimMovementMaxSpeed();

	GetCharacterMovement()->MaxWalkSpeed = CurrentAimingMovementSpeed;
	CurrentRangeWeapon->StartAim();
	OnStartAiming();
}

void AGCBaseCharacter::StopAiming()
{
	if (!bIsAiming)
	{
		return;
	}

	ARangeWeaponItem* CurrentRangeWeapon = GetCharacterEquipmentComponent()->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		CurrentRangeWeapon->StopAim();
	}

	GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeed;
	bIsAiming = false;
	CurrentAimingMovementSpeed = 0.0f;

	OnStopAiming();	
}

void AGCBaseCharacter::Reload()
{
	if (IsValid(CharacterEquipmentComponent->GetCurrentRangeWeapon()))
	{
		CharacterEquipmentComponent->ReloadCurrentWeapon();
	}
}

void AGCBaseCharacter::NextItem()
{
	CharacterEquipmentComponent->EquipNextItem();
}

void AGCBaseCharacter::PreviousItem()
{
	CharacterEquipmentComponent->EquipPreviousItem();
}

void AGCBaseCharacter::OnStartAiming_Implementation()
{
	OnStartAimingInternal();
}

void AGCBaseCharacter::OnStopAiming_Implementation()
{
	OnStopAimingInternal();
}

float AGCBaseCharacter::GetCurrentMovementSpeed() const
{
	
	
	return CurrentAimingMovementSpeed;
}

void AGCBaseCharacter::Falling()
{
	this->GetCharacterMovement()->bNotifyApex = true;
}

void AGCBaseCharacter::NotifyJumpApex()
{
	Super::NotifyJumpApex();
	CurrentFallApex = GetActorLocation();
}

void AGCBaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	float FallHeight = (CurrentFallApex-GetActorLocation()).Z * 0.01f;
	if (IsValid(FallDamageCurve))
	{
		float DamageAmount = FallDamageCurve->GetFloatValue(FallHeight);
		AActor* SelfPointer = Cast<AActor>(this);
		TakeDamage(DamageAmount, FDamageEvent(), GetController(), SelfPointer);
	}
}

const UCharacterEquipmentComponent* AGCBaseCharacter::GetCharacterEquipmentComponent() const
{
	return CharacterEquipmentComponent;
}


UCharacterEquipmentComponent* AGCBaseCharacter::GetCharacterEquipmentComponent_Mutable() const
{
	return CharacterEquipmentComponent;
}

const UCharacterAttributesComponent* AGCBaseCharacter::GetCharacterAttributesComponent() const
{
	return CharacterAttributesComponent;
}

FGenericTeamId AGCBaseCharacter::GetGenericTeamId() const
{
	return FGenericTeamId((uint8)Team);
}

void AGCBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	float Duration = PlayAnimMontage(OnDeathAnimMontage);
	if (Duration == 0.0f)
	{
		EnableRagdoll();
	}
}

void AGCBaseCharacter::EnableRagdoll()
{
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
}

void AGCBaseCharacter::OnStartAimingInternal()
{
	if (OnAimingStateChanged.IsBound())
	{
		OnAimingStateChanged.Broadcast(true);
	}
}

void AGCBaseCharacter::OnStopAimingInternal()
{
	if (OnAimingStateChanged.IsBound())
	{
		OnAimingStateChanged.Broadcast(false);
	}
}
