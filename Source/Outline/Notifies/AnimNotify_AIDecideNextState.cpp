// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AIDecideNextState.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Objects/EnemyStateBase.h"
#include "Outline/Components/StateManagerComponent.h"

void UAnimNotify_AIDecideNextState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (IsValid(OwnerCharacter))
	{
		UStateManagerComponent* StateComponent = OwnerCharacter->GetController()->GetComponentByClass<UStateManagerComponent>();
		UEnemyStateBase* CurrState = Cast<UEnemyStateBase>(StateComponent->GetCurrentActiveState());
		CurrState->DecideNextState();
	}
	
}
