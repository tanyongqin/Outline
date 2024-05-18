// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplaytagContainer.h"
#include "AN_EndAbilityOfGameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UAN_EndAbilityOfGameplayTag : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AbilityToEnd;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
