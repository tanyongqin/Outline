// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Components/AbilityManagerComponent.h"

UAbilityBase::UAbilityBase()
{
}

void UAbilityBase::ConstructAbility()
{
	if (IsValid(PerformingActor))
	{
		OwnerAbilityComponent =  PerformingActor->GetComponentByClass<UAbilityManagerComponent>();
	}

	ReceiveConstructAbility();
}

void UAbilityBase::StartAbility()
{
	OwnerAbilityComponent->SetCurrentActiveAbility(this);
	ReceiveStartAbility();
}

void UAbilityBase::EndAbility()
{
	OwnerAbilityComponent->SetCurrentActiveAbility(nullptr);
	ReceiveEndAbility();
}

bool UAbilityBase::GetIsCurrentAbilityActive()
{
	check(IsValid(OwnerAbilityComponent));

	return (OwnerAbilityComponent->GetCurrentActiveAbility() == this);
}

float UAbilityBase::PlayAbilityMontage(UAnimMontage* MontageToPlay, float InPlayRate, EMontagePlayReturnType ReturnValueType, float InTimeToStartMontageAt, bool bStopAllMontages, FName StartSectionName)
{
	float res = 0.f;
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(PerformingActor);
	if (IsValid(OwnerCharacter))
	{
		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		res = AnimInstance->Montage_Play(
			MontageToPlay,
			InPlayRate,
			ReturnValueType,
			InTimeToStartMontageAt,
			bStopAllMontages
		);

		SetActiveAbilityMontage(MontageToPlay);

		if (StartSectionName != FName("None"))
		{
			AnimInstance->Montage_JumpToSection(StartSectionName, MontageToPlay);
		}
	}
	return res;
}
