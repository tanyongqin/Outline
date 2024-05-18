// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayNextMontage.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UAnimNotify_PlayNextMontage : public UAnimNotify
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	class UAnimMontage* NextMontage;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
