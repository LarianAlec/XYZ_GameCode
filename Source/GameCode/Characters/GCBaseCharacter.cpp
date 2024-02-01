// Alec Larin

#include "GCBaseCharacter.h"
#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/HitResult.h"
#include "GameFramework/Actor.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"

AGCBaseCharacter::AGCBaseCharacter()
{
	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character Attributes"));
	CharacterEquipmentComponent = CreateDefaultSubobject<UCharacterEquipmentComponent>(TEXT("Character Equipment"));
}

void AGCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributesComponent->OnDeathEvent.AddUObject(this, &AGCBaseCharacter::OnDeath);
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
