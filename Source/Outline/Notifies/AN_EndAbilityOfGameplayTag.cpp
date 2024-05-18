// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_EndAbilityOfGameplayTag.h"
#include "Outline/Components/AbilityManagerComponent.h"

void UAN_EndAbilityOfGameplayTag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{	
	if (IsValid(MeshComp->GetOwner()))
	{
		UAbilityManagerComponent* AbilityComp = MeshComp->GetOwner()->GetComponentByClass<UAbilityManagerComponent>();
		if (IsValid(AbilityComp))
		{
			UAbilityBase* FoundAbility = AbilityComp->GetAbilityOfGameplayTag(AbilityToEnd);
			if (IsValid(FoundAbility))
			{
				FoundAbility->EndAbility();
			}			
		}
	}
}
