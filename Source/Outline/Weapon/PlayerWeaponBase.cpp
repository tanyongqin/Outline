// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponBase.h"
#include "Outline/Character/Player/PlayerCharacterBase.h"
#include "Outline/DataAssets/BasePlayer_PDA.h"
#include "Outline/Objects/PlayerStateBase.h"
#include "Outline/Objects/TraceBase.h" 
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/AbilityManagerComponent.h"
#include "Outline/Components/CollisionManagerComponent.h"
#include "Outline/Components/AttributesComponent.h"
#include "Outline/Components/CombatComponent.h"

void APlayerWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	EquipWeapon();
}

void APlayerWeaponBase::EquipWeapon_Implementation()
{
	APlayerCharacterBase* LocalCharacter = Cast<APlayerCharacterBase>(GetOwner());
	if (LocalCharacter)
	{
		UStateManagerComponent* LocalStateManager = LocalCharacter->GetController()->GetComponentByClass<UStateManagerComponent>();
		UAbilityManagerComponent* LocalAbilityManager = LocalCharacter->GetController()->GetComponentByClass<UAbilityManagerComponent>();
		UCollisionManagerComponent* LocalCollisionManager = LocalCharacter->GetController()->GetComponentByClass<UCollisionManagerComponent>();
		UAttributesComponent* LocalAttributesComponent = LocalCharacter->GetController()->GetComponentByClass<UAttributesComponent>();
		UCombatComponent* LocalCombatComponent = LocalCharacter->GetController()->GetComponentByClass<UCombatComponent>();

		LocalStateManager->ClearStatesComponent();
		LocalAbilityManager->ClearAbilityComponent();

		// Initialize State
		for (TSubclassOf<UPlayerStateBase> PlayerStateBase : AssociatedDataAsset->StatesToCreate)
		{
			UStateBase* ConstructedState = nullptr;
			LocalStateManager->ConstructStateOfClass(PlayerStateBase, ConstructedState);
		}
		UStateBase* IdleState = LocalStateManager->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Idle")));
		LocalStateManager->PerformStateOfClass(IdleState->GetClass());

		// Initialize Attributes
		LocalAttributesComponent->AssignAttributes(AssociatedDataAsset->AttributesToCreate);

		// Initialize Equipped Weapon  Of Combat Component
		LocalCombatComponent->SetEquippedWeapon(this);

		// Initialize Collision
		UTraceBase* CreatedTraceObject = nullptr;
		LocalCollisionManager->ConstructTraceOfClass(UTraceBase::StaticClass(), CreatedTraceObject);

		if (IsValid(CreatedTraceObject))
		{
			CreatedTraceObject->TraceGameplayTag = FGameplayTag::RequestGameplayTag(FName("Trace.Right Hand Weapon"));
			TArray<FName> PrimitiveComponentSocketNames;
			PrimitiveComponentSocketNames.Add(FName("Weapon Trace 1"));
			PrimitiveComponentSocketNames.Add(FName("Weapon Trace 2"));
			PrimitiveComponentSocketNames.Add(FName("Weapon Trace 3"));
			CreatedTraceObject->SetTraceMeshInfo(LocalCharacter->GetMesh(), PrimitiveComponentSocketNames);
		}
	}
}

void APlayerWeaponBase::UnEquipWeapon_Implementation()
{
	APlayerCharacterBase* LocalCharacter = Cast<APlayerCharacterBase>(GetOwner());
	if (LocalCharacter)
	{
		UCollisionManagerComponent* LocalCollisionManager = GetOwner()->GetComponentByClass<UCollisionManagerComponent>();
		UCombatComponent* LocalCombatComponent = GetOwner()->GetComponentByClass<UCombatComponent>();
		LocalCollisionManager->ClearAvailableTraceObjects();
		LocalCharacter->AssignMoveset(EMoveset::EM_COMMON);
		LocalCombatComponent->ModifyCombatStatus(FGameplayTag::RequestGameplayTag(FName("Status.Combat.InCombat")), EModifyingType::Remove);
	}
}

void APlayerWeaponBase::SetAttributesAndStates()
{
	APlayerCharacterBase* LocalCharacter = Cast<APlayerCharacterBase>(GetOwner());
	if (IsValid(LocalCharacter))
	{
		UStateManagerComponent* LocalStateManager = LocalCharacter->GetController()->GetComponentByClass<UStateManagerComponent>();
		UAbilityManagerComponent* LocalAbilityManager = LocalCharacter->GetComponentByClass<UAbilityManagerComponent>();
		UAttributesComponent* LocalAttributesComponent = LocalCharacter->GetComponentByClass<UAttributesComponent>();
		if (IsValid(LocalStateManager) && IsValid(LocalAbilityManager) && IsValid(LocalAttributesComponent))
		{
			LocalStateManager->ClearStatesComponent();
			LocalAbilityManager->ClearAbilityComponent();
			LocalAttributesComponent->ClearAttributes();			

			for (TSubclassOf<UPlayerStateBase> StateToConstruct : AssociatedDataAsset->StatesToCreate)
			{
				UStateBase* ConstructedState = nullptr;
				LocalStateManager->ConstructStateOfClass(StateToConstruct, ConstructedState);				
			}

			UStateBase* IdleState = LocalStateManager->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Idle")));
			LocalStateManager->PerformStateOfClass(IdleState->GetClass());

			LocalAttributesComponent->AssignAttributes(AssociatedDataAsset->AttributesToCreate);
		}
	}
}
