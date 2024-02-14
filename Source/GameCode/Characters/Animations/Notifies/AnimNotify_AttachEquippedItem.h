// Alec Larin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttachEquippedItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMECODE_API UAnimNotify_AttachEquippedItem : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
