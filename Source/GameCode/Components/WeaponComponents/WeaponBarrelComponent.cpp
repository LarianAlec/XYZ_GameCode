// Alec Larin


#include "WeaponBarrelComponent.h"
#include "GameCodeTypes.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"



void UWeaponBarrelComponent::Shot(FVector ShotStart, FVector ShotDirection, AController* Controller)
{
	FVector MuzzleLocation	= GetComponentLocation();
 	FVector ShotEnd = ShotStart + FiringRange * ShotDirection;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlashFX, MuzzleLocation, GetComponentRotation());

	FHitResult ShotResult;
	if (GetWorld()->LineTraceSingleByChannel(ShotResult, ShotStart, ShotEnd, ECC_Bullet))
	{
		ShotEnd = ShotResult.ImpactPoint;
		AActor* HitActor = ShotResult.GetActor();
		if (IsValid(HitActor))
		{
			HitActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, GetOwner());
		}

		DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, FColor::Red, false, 1.0f);
	}
	DrawDebugLine(GetWorld(), MuzzleLocation, ShotEnd, FColor::Red, false, 1.0f, 0, 3.0f);
}
