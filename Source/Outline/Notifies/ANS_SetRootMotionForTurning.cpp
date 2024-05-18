// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_SetRootMotionForTurning.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Components/EnemyCombatComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"

void UANS_SetRootMotionForTurning::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	OwnerCharacter = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = true;
	}
}

void UANS_SetRootMotionForTurning::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(OwnerCharacter))
	{
		UEnemyCombatComponent* CombatComp = OwnerCharacter->GetComponentByClass<UEnemyCombatComponent>();
		CombatComp->RotateEnemyToCombatTarget();
	}
}

void UANS_SetRootMotionForTurning::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = false;
	}
}
