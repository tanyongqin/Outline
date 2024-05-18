// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_UpdateDie.h"
#include "Outline/Character/Player/SamuraiAnimInstance.h"

void UAnimNotify_UpdateDie::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	USamuraiAnimInstance* AnimInstace = Cast<USamuraiAnimInstance>(MeshComp->GetAnimInstance());
	if (IsValid(AnimInstace))
	{
		AnimInstace->SetIsDie(true);
	}
}
