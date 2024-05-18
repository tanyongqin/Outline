// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_PlayNextMontage.h"

void UAnimNotify_PlayNextMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(NextMontage))
	{
		MeshComp->GetAnimInstance()->Montage_Play(NextMontage);
	}
}
