// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_InputBuffer.h"
#include "GameFramework/Character.h"
#include "Outline/Objects/PlayerStateBase.h"
#include "Outline/Components/StateManagerComponent.h"

void UANS_InputBuffer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (IsValid(OwnerCharacter))
	{
		if (IsValid(OwnerCharacter->GetController()))
		{
			UStateManagerComponent* StateComp = OwnerCharacter->GetController()->GetComponentByClass<UStateManagerComponent>();
			if (!IsValid(StateComp) || !StateToModify.IsValid())
			{
				return;
			}

			UBufferingBase* InputBuffer = NewObject<UBufferingBase>(OwnerCharacter, BufferingClass);
			if (!IsValid(InputBuffer))
			{
				return;
			}

			InputBuffer->BufferGameplayTag = BufferGameplayTag;
			InputBuffer->AllowedInputActions = AllowedInputs;
			InputBuffer->SetBufferingState(NotifyInputBufferType);
			SetBufferingObject(InputBuffer);

			UPlayerStateBase* ModifyByState = Cast<UPlayerStateBase>(StateComp->GetStateOfGameplayTag(StateToModify));
			ModifyByState->AddBufferingObject(InputBuffer);
		}
	}
}

void UANS_InputBuffer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(GetBufferingObject()))
	{
		GetBufferingObject()->EndBufferingObject();
	}
}
