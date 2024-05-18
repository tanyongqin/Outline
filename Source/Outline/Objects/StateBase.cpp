// Fill out your copyright notice in the Description page of Project Settings.


#include "StateBase.h"
#include "TimerManager.h"
#include "Outline/Objects/AbilityBase.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/AbilityManagerComponent.h"

UStateBase::UStateBase()
{
}

void UStateBase::ConstructState()
{
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(PerformingActor);
	if (IsValid(OwnerCharacter))
	{
		OwnerStateManager = OwnerCharacter->GetController()->GetComponentByClass<UStateManagerComponent>();
	}

}

void UStateBase::StartState()
{
	if (OwnerStateManager)
	{
		OwnerStateManager->SetCurrentActiveState(this);
	}

	ReceiveStartState();
}

void UStateBase::EndState()
{
	if (OwnerStateManager && OwnerStateManager->GetCurrentActiveState() == this)
	{
		OwnerStateManager->SetCurrentActiveState(nullptr);
		ClearStateValues();
	}

	ReceiveEndState();
}

bool UStateBase::RestartState(bool ConditionCheck)
{
	if (!ConditionCheck || CanPerformState())
	{
		PrepareStateValues();
		StartState();
		return true;
	}
	return false;
}

void UStateBase::ClearStateValues()
{
	GetWorld()->GetTimerManager().PauseTimer(PassedTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(PassedTimerHandle);
	ClearPassedTime();
}

void UStateBase::PrepareStateValues_Implementation()
{
	ClearPassedTime();
}

void UStateBase::StartStateTimer()
{
	if (bTimeControlledState)
	{
		GetWorld()->GetTimerManager().SetTimer(PassedTimerHandle, this, &UStateBase::IncrementPassedTime, TimerUpdateRate, true);
	}
}

void UStateBase::IncrementPassedTime()
{
	if (IsValid(OwnerStateManager))
	{
		if (IsValid(OwnerStateManager->GetCurrentActiveState()) && OwnerStateManager->GetCurrentActiveState() == this)
		{
			IncrementTimeByUpdateRate();

			// 到时间, 清除
			if (TimePassed >= StateTimeLimit)
			{
				ClearPassedTime();
			}
		}
		else
		{
			EndState();
		}
	}
}

void UStateBase::ClearPassedTime()
{
	TimePassed = 0.f;
}

void UStateBase::StopStateTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(PassedTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(PassedTimerHandle);
	ClearPassedTime();
}

float UStateBase::IncrementTimeByUpdateRate()
{
	TimePassed = TimePassed + TimerUpdateRate;
	return TimePassed;
}

bool UStateBase::CheckAbilitiesToRun(TArray<TSubclassOf<UAbilityBase>> AbilitiesToCheck)
{
	AActor* CurrentPerformingActor;
	GetPerformingActor(CurrentPerformingActor);

	UAbilityManagerComponent* OwnerAbilityManager = CurrentPerformingActor->GetComponentByClass<UAbilityManagerComponent>();
	if (IsValid(OwnerAbilityManager))
	{
		for (TSubclassOf<UAbilityBase> ClassOfAbility : AbilitiesToCheck)
		{
			if (OwnerAbilityManager->GetCanPerformAbilityOfClass(ClassOfAbility))
			{				
				SelectedAbilityToTrigger = ClassOfAbility;
				return true;
			}
		}
	}	
	return false;
}

bool UStateBase::CanSetAsQueueState()
{
	return false;
}
