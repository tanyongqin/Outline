// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyControllerBase.h"
#include "Outline/Objects/EnemyStateBase.h"
#include "Outline/Character/Enemy/EnemyCharacterBase.h"
#include "Outline/DataAssets/BaseEnemy_PDA.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/AbilityManagerComponent.h"
#include "Outline/Components/EnemyCombatComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"


AEnemyControllerBase::AEnemyControllerBase()
{
	OwnerStateComponent = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateComp"));
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void AEnemyControllerBase::InitializeAIController()
{
	OwnerCharacter = Cast<AEnemyCharacterBase>(GetPawn());

	if (IsValid(OwnerCharacter->AssociatedDataAsset))
	{
		OwnerStateComponent->InitializeStateManagerComponent(GetPawn());

		if (IsValid(OwnerCharacter->AssociatedDataAsset->BehaviorTree))
		{
			RunBehaviorTree(OwnerCharacter->AssociatedDataAsset->BehaviorTree);
			
			OwnerStateComponent->TryPerformStateOfClass(OwnerCharacter->AssociatedDataAsset->OnSpawnState, true);
			OwnerStateComponent->OnUpdatedActiveState.AddDynamic(this, &AEnemyControllerBase::ReceiveStateUpdate);

			AIPerception->ForgetAll();

			UAbilityManagerComponent* OwnerAbilityComponent = OwnerCharacter->GetComponentByClass<UAbilityManagerComponent>();
			OwnerAbilityComponent->OnUpdatedActiveAbility.AddDynamic(this, &AEnemyControllerBase::ReceiveAbilityUpdate);
		}
	}

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyControllerBase::ReceiveTargetPerceptionUpdated);

}

void AEnemyControllerBase::ReceiveAbilityUpdate()
{
	UAbilityManagerComponent* OwnerAbilityComponent = GetPawn()->GetComponentByClass<UAbilityManagerComponent>();
	Blackboard->SetValueAsObject(FName("AbilityValue"), OwnerAbilityComponent->GetCurrentActiveAbility());
}

void AEnemyControllerBase::ReceiveStateUpdate()
{
	Blackboard->SetValueAsObject(FName("StateValue"), OwnerStateComponent->GetCurrentActiveState());
}

void AEnemyControllerBase::ReceiveTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	bool CanPerceive = IsValid(Blackboard) 
		&& IsValid(OwnerStateComponent->GetCurrentActiveState()) 
		&& (OwnerStateComponent->GetCurrentActiveState()->StateGameplayTag != FGameplayTag::RequestGameplayTag(FName("State.Death")));
	if (CanPerceive)
	{
		ACharacterBase* Target = Cast<ACharacterBase>(Actor);
		if (!IsValid(Target)) return;

		if (!IsValid(OwnerCharacter->AssociatedDataAsset)) return;

		FGameplayTagContainer TagContainer;
		Target->GetOwnedGameplayTags(TagContainer);

		if (Stimulus.WasSuccessfullySensed() && TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.Player"))))
		{
			if (IsValid(OwnerCharacter->GetCombatComponent()->GetCombatTarget()))
			{
				OwnerCharacter->GetCombatComponent()->AddCombatTarget(Actor);
			}
			else
			{
				OwnerCharacter->GetCombatComponent()->AddCombatTarget(Actor);
				OwnerCharacter->GetCombatComponent()->SetCombatTarget(Actor);
				OwnerCharacter->GetCombatComponent()->EnterCombat();
			}
		}
	}
}

