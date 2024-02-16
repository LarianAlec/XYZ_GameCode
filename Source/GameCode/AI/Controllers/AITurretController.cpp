// Alec Larin


#include "AI/Controllers/AITurretController.h"
#include "AI/Characters/Turret.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionComponent.h"

void AAITurretController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (IsValid(InPawn))
	{
		checkf(InPawn->IsA<ATurret>(), TEXT("AAITurretController::SetPawn AAITurretControoler can possess only Turrets"));
		CachedTurret = StaticCast<ATurret*>(InPawn);
	}
	else
	{
		CachedTurret = nullptr;
	}
}

void AAITurretController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if(!CachedTurret.IsValid())
	{
		return;
	}

	AActor* ClosestActor = GetClosestSensedActor(UAISense_Sight::StaticClass());
	CachedTurret->SetCurrentTarget(ClosestActor);
	
}
