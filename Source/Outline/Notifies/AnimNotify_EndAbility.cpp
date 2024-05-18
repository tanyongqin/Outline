// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndAbility.h"
#include "Outline/Components/AbilityManagerComponent.h"

void UAnimNotify_EndAbility::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(MeshComp->GetOwner()))
	{
		UAbilityManagerComponent* AbilityComp = MeshComp->GetOwner()->GetComponentByClass<UAbilityManagerComponent>();
		if (IsValid(AbilityComp) && IsValid(AbilityComp->GetCurrentActiveAbility()))
		{
			AbilityComp->GetCurrentActiveAbility()->EndAbility();
		}
	}
}
