// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GCBaseCharacter.generated.h"

UCLASS(Abstract, NotBlueprintable)
class GAMECODE_API AGCBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGCBaseCharacter();

	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) {};

	virtual void MoveRight(float Value) {};

	virtual void Turn(float Value) {};

	virtual void LookUp(float Value) {};


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	class UCharacterAttributesComponent* CharacterAttributesComponent;

	virtual void OnDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character| Animations")
	class UAnimMontage* OnDeathAnimMontage;

	void EnableRagdoll();
};
