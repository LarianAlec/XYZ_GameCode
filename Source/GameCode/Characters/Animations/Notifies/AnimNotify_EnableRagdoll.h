// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EnableRagdoll.generated.h"

/**
 * 
 */
UCLASS()
class GAMECODE_API UAnimNotify_EnableRagdoll : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshCompo, UAnimSequenceBase* Animation);
};
