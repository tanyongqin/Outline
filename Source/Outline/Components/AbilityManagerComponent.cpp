// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityManagerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UAbilityManagerComponent::UAbilityManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PassiveAbilities.Num() > 0) 
	{
		for (int32 i = 0; i < PassiveAbilities.Num(); i++)
		{
			if (PassiveAbilities[i]) 
			{
				PassiveAbilities[i]->TickAbility(DeltaTime);
			}
		}
	}

	if (CurrentActiveAbility)
	{
		CurrentActiveAbility->TickAbility(DeltaTime);
	}
}

void UAbilityManagerComponent::InitializeAbilitySystemComponent_Implementation()
{

}

void UAbilityManagerComponent::PerformAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSet)
{
	TryPerformAbilityOfClass(AbilityToSet, false);
}

bool UAbilityManagerComponent::TryPerformAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSet, bool ConditionCheck)
{
	if (AbilityToSet)
	{
		UAbilityBase* LocalAbility = nullptr;
		GetAbilityOfClass(AbilityToSet, LocalAbility);

		if (LocalAbility == nullptr)
		{
			ConstructAbilityOfClass(AbilityToSet, LocalAbility);
		}

		if (LocalAbility == nullptr) return false;

		if (ConditionCheck)
		{
			if (LocalAbility->CanPerformAbility())
			{
				LocalAbility->StartAbility();
				return true;
			}
		}
		else
		{
			LocalAbility->StartAbility();
			return true;
		}
	}
	
	return false;
}

bool UAbilityManagerComponent::TryPerformAbilitiesOfClass(TArray<TSubclassOf<UAbilityBase>> AbilitiesToSet, bool ConditionCheck)
{
	bool LocalBool = false;
	for (int32 i = 0; i < AbilitiesToSet.Num(); i++)
	{
		if (AbilitiesToSet[i])
		{
			LocalBool = TryPerformAbilityOfClass(AbilitiesToSet[i], ConditionCheck);
			if (LocalBool)
			{
				return true;
			}
		}

	}
	return false;
}

void UAbilityManagerComponent::SetCurrentActiveAbility(UAbilityBase* NewCurrentActiveAbility)
{
	CurrentActiveAbility = NewCurrentActiveAbility;
	OnUpdatedActiveAbility.Broadcast();

	if (NewCurrentActiveAbility && PassiveAbilities.Num() > 0)
	{
		for (int32 i = 0; i < PassiveAbilities.Num(); i++)
		{
			// 原来是被动, 现在作为主动激活. 所以移除?
			if (PassiveAbilities[i] == NewCurrentActiveAbility)
			{
				RemoveFromPassiveAbilities(NewCurrentActiveAbility);
			}
		}
	}
}

void UAbilityManagerComponent::SetAsPassiveAbility(UAbilityBase* NewPassiveAbility)
{
	if (NewPassiveAbility)
	{
		PassiveAbilities.AddUnique(NewPassiveAbility);
		if (NewPassiveAbility == CurrentActiveAbility)
		{
			CurrentActiveAbility = nullptr;
		}
	}
}

UAbilityBase* UAbilityManagerComponent::GetCurrentActiveAbility()
{
	return CurrentActiveAbility;
}

void UAbilityManagerComponent::GetAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSearch, UAbilityBase*& FoundAbility)
{
	for (int32 i = 0; i < ActivatableAbilities.Num(); i++)
	{
		if (ActivatableAbilities[i] && ActivatableAbilities[i]->GetClass() == AbilityToSearch)
		{
			FoundAbility = ActivatableAbilities[i];
			return;
		}
	}
	FoundAbility = nullptr;
}

bool UAbilityManagerComponent::GetCanPerformAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSearch)
{
	if (AbilityToSearch)
	{
		UAbilityBase* LocalAbility = nullptr;
		GetAbilityOfClass(AbilityToSearch, LocalAbility);

		if (LocalAbility)
		{
			return LocalAbility->CanPerformAbility();
		}
		else
		{
			UAbilityBase* LocalNewAbility;
			ConstructAbilityOfClass(AbilityToSearch, LocalNewAbility);
			return LocalNewAbility->CanPerformAbility();
		}
	}
	return false;
}

void UAbilityManagerComponent::GetChildAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSearch, UAbilityBase*& FoundAbility)
{
	if (AbilityToSearch)
	{
		for (int32 i = 0; i < ActivatableAbilities.Num(); i++)
		{
			if (ActivatableAbilities[i])
			{
				if (UKismetMathLibrary::ClassIsChildOf(ActivatableAbilities[i]->GetClass(), AbilityToSearch))
				{
					FoundAbility = ActivatableAbilities[i];
					return;
				}
			}
		}

		FoundAbility = nullptr;
		return;
	}
}

UAbilityBase* UAbilityManagerComponent::GetAbilityOfGameplayTag(FGameplayTag AbilityGameplayTag)
{
	UAbilityBase* LocalAbility = nullptr;
	for (int32 i = 0; i < ActivatableAbilities.Num(); i++)
	{
		if (ActivatableAbilities[i])
		{
			if (ActivatableAbilities[i]->AbilityGameplayTag == AbilityGameplayTag)
			{
				LocalAbility = ActivatableAbilities[i];
				return LocalAbility;
			}
		}
	}

	return LocalAbility;
}

void UAbilityManagerComponent::ConstructAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToConstruct, UAbilityBase*& ConstructedAbility)
{
	ConstructedAbility = nullptr;
	if (AbilityToConstruct)
	{
		UAbilityBase* LocalNewAbility;
		LocalNewAbility = NewObject<UAbilityBase>(GetOwner(), AbilityToConstruct);

		ActivatableAbilities.AddUnique(LocalNewAbility);
		LocalNewAbility->SetPerformingActor(GetOwner());
		LocalNewAbility->ConstructAbility();
		ConstructedAbility = LocalNewAbility;
	}
}

