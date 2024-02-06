// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GCBaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAimStateChanged, bool)

class UCharacterAttributesComponent;
class UCharacterEquipmentComponent;
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

	void StartFire();

	void StopFire();

	void StartAiming();

	void StopAiming();

	void Reload() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	void OnStartAiming();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	void OnStopAiming();

	float GetCurrentMovementSpeed() const;

	virtual void Falling() override;

	virtual void NotifyJumpApex() override;

	virtual void Landed(const FHitResult& Hit) override;

	const UCharacterEquipmentComponent* GetCharacterEquipmentComponent() const;

	UCharacterEquipmentComponent* GetCharacterEquipmentComponent_Mutable() const;

	const UCharacterAttributesComponent* GetCharacterAttributesComponent() const;

	bool IsAiming() const { return bIsAiming; }

	FOnAimStateChanged OnAimingStateChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterAttributesComponent* CharacterAttributesComponent;

	virtual void OnDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character| Animations")
	class UAnimMontage* OnDeathAnimMontage;

	void EnableRagdoll();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Attributes")
	class UCurveFloat* FallDamageCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterEquipmentComponent* CharacterEquipmentComponent;

	virtual void OnStartAimingInternal();

	virtual void OnStopAimingInternal();

private:
	FVector CurrentFallApex;

	bool bIsAiming = false;

	float CurrentAimingMovementSpeed = 0.0f;

	float MaxMovementSpeed = 0.0f;
};
