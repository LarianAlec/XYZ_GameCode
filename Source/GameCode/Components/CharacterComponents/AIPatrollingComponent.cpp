// Alec Larin


#include "Components/CharacterComponents/AIPatrollingComponent.h"
#include "Actors/Navigation/PatrollingPath.h"



bool UAIPatrollingComponent::CanPatrol() const
{

	return IsValid(PatrollingPath) && PatrollingPath->GetWaypoints().Num() > 0;
}

FVector UAIPatrollingComponent::SelectClosestWaypoint()
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	const TArray<FVector> WayPoints = PatrollingPath->GetWaypoints();
	FTransform PathTransform = PatrollingPath->GetActorTransform();

	FVector ClosestWayPoint;
	float MinSquearedDistance = FLT_MAX;
	for (int32 i = 0; i < WayPoints.Num(); ++i)
	{
		FVector WayPointWorld = PathTransform.TransformPosition(WayPoints[i]);
		float CurrentSquearedDistance = (OwnerLocation - WayPointWorld).SizeSquared();
		if (CurrentSquearedDistance < MinSquearedDistance)
		{
			ClosestWayPoint = WayPointWorld;
			CurrentWayPointIndex = i;
		}
	}
	return ClosestWayPoint;
}

FVector UAIPatrollingComponent::SelectNextWaypoint()
{
	++CurrentWayPointIndex;
	const TArray<FVector> WayPoints = PatrollingPath->GetWaypoints();
	if (CurrentWayPointIndex == PatrollingPath->GetWaypoints().Num())
	{
		CurrentWayPointIndex = 0;
	}
	FTransform PathTransform = PatrollingPath->GetActorTransform();
	FVector WayPoint = PathTransform.TransformPosition(WayPoints[CurrentWayPointIndex]);
	return WayPoint;
}
