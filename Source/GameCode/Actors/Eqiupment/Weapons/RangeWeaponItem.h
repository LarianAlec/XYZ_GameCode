// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Actors/Eqiupment/EquipableItem.h"
#include "RangeWeaponItem.generated.h"


class UAnimMontage;

UCLASS(Blueprintable)
class GAMECODE_API ARangeWeaponItem : public AEquipableItem
{
	GENERATED_BODY()
	
public:
	ARangeWeaponItem();

	void Fire();

	FTransform GetForeGripTransform() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UWeaponBarrelComponent* WeaponBarrel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Weapon")
	UAnimMontage* WeaponFireMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Animations | Character")
	UAnimMontage* CharacterFireMontage;

private:
	float PlayAnimMontage(UAnimMontage* AnimMontage);
};
