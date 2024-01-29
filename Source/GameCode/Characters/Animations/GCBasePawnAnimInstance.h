// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GCBasePawnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMECODE_API UGCBasePawnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Base pawn animation instance")
	float InputForward;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Base pawn animation instance")
	float InputRight;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Base pawn animation instance")
	bool bIsInAir;

private:
	TWeakObjectPtr<class AGameCodeBasePawn> CachedBasePawn;
};
