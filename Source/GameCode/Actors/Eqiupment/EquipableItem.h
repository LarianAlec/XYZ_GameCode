// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCodeTypes.h"
#include "EquipableItem.generated.h"


class UAnimMontage;
UCLASS(Abstract, NotBlueprintable)
class GAMECODE_API AEquipableItem : public AActor
{
	GENERATED_BODY()

public:
	EEquipableItemType GetItemType() const;

	UAnimMontage* GetCharacterEquipAnimMontage() const;

	FName GetUnEquippedSocketName() const;

	FName GetEquippedSocketName() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable item")
	EEquipableItemType ItemType = EEquipableItemType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable item")
	UAnimMontage* CharacterEquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable item")
	FName UnEquippedSocketName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable item")
	FName EquippedSocketName = NAME_None;
};
