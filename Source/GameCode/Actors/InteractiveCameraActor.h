// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "InteractiveCameraActor.generated.h"


UCLASS()
class GAMECODE_API AInteractiveCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AInteractiveCameraActor();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition settings")
	float TransitionToCameraTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition settings")
	float TransitionToPawnTime = 1.0f;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
