// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "ANS_Trace.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UANS_Trace : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> TraceToToggle;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Attack Properties")
	class UAttackProperties* AttackProperty;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	class UCollisionManagerComponent* CollisionComp;
};
