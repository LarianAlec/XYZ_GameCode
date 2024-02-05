// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameCodeTypes.h"
#include "CharacterEquipmentComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentWeaponAmmoChanged, int32);

class ARangeWeaponItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMECODE_API UCharacterEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	EEquipableItemType GetCurrentEquippedItemType() const;

	ARangeWeaponItem* GetCurrentRangeWeapon() const;

	FOnCurrentWeaponAmmoChanged OnCurrentWeaponAmmoChangedEvent;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	TSubclassOf<ARangeWeaponItem> SideArmClass;

private:
	void CreateLoadout();

	UFUNCTION()
	void OnCurrentWeaponAmmoChanged(int32 Ammo);

	ARangeWeaponItem* CurrentEquippedWeapon;
	TWeakObjectPtr<class AGCBaseCharacter> CachedBaseCharacter;
};
