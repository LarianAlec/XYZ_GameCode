// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponBarrelComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMECODE_API UWeaponBarrelComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	void Shot(FVector ShotStart, FVector ShotDirection, AController* Controller);
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes")
	float FiringRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes | Damage")
	float DamageAmount = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes | VFX")
	UNiagaraSystem* MuzzleFlashFX;
};
