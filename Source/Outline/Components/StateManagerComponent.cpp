// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManagerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UStateManagerComponent::UStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UStateManagerComponent::InitializeStateManagerComponent_Implementation(AActor* NewPerformingActor)
{
	PerformingActor = NewPerformingActor;	
}

// Called every frame
void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentActiveState)
	{
		CurrentActiveState->TickState(DeltaTime);
	}
}

void UStateManagerComponent::PerformStateOfClass(TSubclassOf<UStateBase> StateToSet)
{
	TryPerformStateOfClass(StateToSet, false);
}

bool UStateManagerComponent::TryPerformStateOfClass(TSubclassOf<UStateBase> StateToSet, bool ConditionCheck)
{
	if (StateToSet)
	{
		UStateBase* FoundState = nullptr;
		GetStateOfClass(StateToSet, FoundState);

		// 如果为空, 构建
		if (FoundState == nullptr)
		{
			ConstructStateOfClass(StateToSet, FoundState);
		}

		if (FoundState == nullptr)
		{
			return false;
		}

		// 校验是否可执行
		if (ConditionCheck && !FoundState->CanPerformState())
		{
			return false;
		}

		if (IsValid(CurrentActiveState) && CurrentActiveState!= FoundState)
		{
			CurrentActiveState->EndState();
		}

		FoundState->PrepareStateValues();
		CurrentActiveState = FoundState;

		CurrentActiveState->StartState();
		OnUpdatedActiveState.Broadcast();

		return true;
	}
	return false;
}


bool UStateManagerComponent::TryPerformStatesOfClass(TArray <TSubclassOf<UStateBase>> StatesToSet, bool ConditionCheck)
{
	bool LocalBool = false;
	for (int32 i = 0; i < StatesToSet.Num(); i++)
	{
		if (StatesToSet[i])
		{
			LocalBool = TryPerformStateOfClass(StatesToSet[i], ConditionCheck);
			if (LocalBool)
			{
				return true;
			}
		}

	}
	return false;
}

void UStateManagerComponent::TrySetQueuedState(TSubclassOf<UStateBase> StateToQueue, bool ConditionCheck)
{
	if (StateToQueue)
	{
		if (ConditionCheck)
		{
			if (GetCanSetQueuedStateOfClass(StateToQueue))
			{
				AddToQueuedStates(StateToQueue);
			}
		}
		else
		{
			AddToQueuedStates(StateToQueue);
		}
	}
}

void UStateManagerComponent::SetCurrentActiveState(UStateBase* NewCurrentActiveState)
{
	CurrentActiveState = NewCurrentActiveState;
	OnUpdatedActiveState.Broadcast();
}

void UStateManagerComponent::GetStateOfClass(TSubclassOf<UStateBase> StateToSearch, UStateBase*& FoundState)
{
	for (int32 i = 0; i < ActivatableStates.Num(); i++)
	{

		if (ActivatableStates[i])
		{
			if (ActivatableStates[i]->GetClass() == StateToSearch)
			{
				FoundState = ActivatableStates[i];

				return;
			}
		}

	}

	FoundState = nullptr;
	return;
}

void UStateManagerComponent::GetChildStateOfClass(TSubclassOf<UStateBase> StateToSearch, UStateBase*& FoundState)
{
	for (int32 i = 0; i < ActivatableStates.Num(); i++)
	{
		if (ActivatableStates[i])
		{
			if (UKismetMathLibrary::ClassIsChildOf(ActivatableStates[i]->GetClass(), StateToSearch))
			{
				FoundState = ActivatableStates[i];

				return;
			}
		}
	}

	FoundState = nullptr;
	return;
}

bool UStateManagerComponent::GetCanPerformStateOfClass(TSubclassOf<UStateBase> ClassToLookFor)
{
	if (ClassToLookFor)
	{
		UStateBase* LocalState = nullptr;
		GetStateOfClass(ClassToLookFor, LocalState);

		if (LocalState)
		{
			return LocalState->CanPerformState();
		}
		else
		{
			UStateBase* LocalNewState;
			ConstructStateOfClass(ClassToLookFor, LocalNewState);

			return LocalNewState->CanPerformState();
		}
	}
	return false;

}

bool UStateManagerComponent::GetCanSetQueuedStateOfClass(TSubclassOf<UStateBase> StateToSearch)
{
	UStateBase* LocalState = nullptr;
	GetStateOfClass(StateToSearch, LocalState);

	if (LocalState)
	{
		return LocalState->CanSetAsQueueState();
	}
	else
	{
		UStateBase* LocalNewState;
		ConstructStateOfClass(StateToSearch, LocalNewState);

		return LocalNewState->CanSetAsQueueState();
	}
}


UStateBase* UStateManagerComponent::GetStateOfGameplayTag(FGameplayTag StateGameplayTag)
{

	UStateBase* LocalState = nullptr;
	for (int32 i = 0; i < ActivatableStates.Num(); i++)
	{
		if (ActivatableStates[i])
		{
			if (ActivatableStates[i]->StateGameplayTag == StateGameplayTag)
			{
				LocalState = ActivatableStates[i];
				return LocalState;
			}
		}
	}

	return LocalState;
}

void UStateManagerComponent::ConstructStateOfClass(TSubclassOf<UStateBase> StateToConstruct, UStateBase*& ConstructedState)
{
	ConstructedState = nullptr;
	if (StateToConstruct)
	{
		UStateBase* LocalNewState;
		LocalNewState = NewObject<UStateBase>(GetOwner(), StateToConstruct);

		ActivatableStates.AddUnique(LocalNewState);
		LocalNewState->SetPerformingActor(PerformingActor);
		LocalNewState->ConstructState();
		ConstructedState = LocalNewState;
	}

}

