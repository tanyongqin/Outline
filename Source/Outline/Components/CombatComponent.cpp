// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "Outline/Objects/BuffBase.h"
#include "Outline/Objects/ConditionBase.h"
#include "Outline/Objects/AttackProperties.h"
#include "Outline/Objects/DefenseProperties.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::ModifyCombatStatus(FGameplayTag CombatStatusToModify, EModifyingType ModifyType)
{
	if (ModifyType == EModifyingType::Add)
	{
		CombatStatusContainer.AddTag(CombatStatusToModify);
	}
	else
	{
		CombatStatusContainer.RemoveTag(CombatStatusToModify);
	}
}

UConditionBase* UCombatComponent::GetCombatConditionOfGameplayTag(FGameplayTag ConditionGameplayTag)
{
	UConditionBase* LocalCondition = nullptr;
	for (int32 i = 0; i < CombatConditions.Num(); i++)
	{
		if (CombatConditions[i])
		{
			if (CombatConditions[i]->ConditionGameplayTag == ConditionGameplayTag)
			{
				LocalCondition = CombatConditions[i];
				return LocalCondition;
			}
		}
	}

	return LocalCondition;
}

void UCombatComponent::ConstructDefensePropertyOfClass(TSubclassOf<UDefenseProperties> PropertyToConstruct, UDefenseProperties*& ConstructedProperty)
{
	ConstructedProperty = nullptr;
	if (PropertyToConstruct)
	{
		UDefenseProperties* LocalNewProperty;
		LocalNewProperty = NewObject<UDefenseProperties>(GetOwner(), PropertyToConstruct);

		LocalNewProperty->SetDefensePropertyOwner(GetOwner());
		LocalNewProperty->ConstructDefenseProperty();
		ConstructedProperty = LocalNewProperty;
	}
}


