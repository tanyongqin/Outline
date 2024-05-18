// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_SetMontagePlayRate.h"

void UANS_SetMontagePlayRate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	UAnimMontage* Montage = Cast<UAnimMontage>(Animation);
	if (IsValid(Montage))
	{
		MeshComp->GetAnimInstance()->Montage_SetPlayRate(Montage, BeginPlayRate);
	}
}

void UANS_SetMontagePlayRate::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UAnimMontage* Montage = Cast<UAnimMontage>(Animation);
	if (IsValid(Montage))
	{
		MeshComp->GetAnimInstance()->Montage_SetPlayRate(Montage, EndPlayRate);
	}
}
