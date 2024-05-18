// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseProperties.h"
#include "Outline/Effects/ImpactEffects.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Objects/StateBase.h"
#include "Outline/Objects/AttackProperties.h"
#include "Outline/Components/CombatComponent.h"
#include "Outline/Components/StateManagerComponent.h"


#include "Outline/Components/EnemyCombatComponent.h"
#include "Outline/Controller/PlayerControllerBase.h"
#include "Outline/HUD/GameHUD.h"
#include "Outline/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"

void UDefenseProperties::ConstructDefenseProperty()
{
	OwnerCombatComponent = GetDefensePropertyOwner()->GetComponentByClass<UCombatComponent>();
}

void UDefenseProperties::ProcessReceivedAttack()
{
	DetermineImpactResult();
	
	OwnerCombatComponent->ReceivedAttackProperty->ProcessAttackPropertry();

	// SetDefenseImpactValues();

	ApplyImpactHitReactions();

	ApplyImpactAttributes();

	// ApplyImpactBuffsAndDebuffs();
}

void UDefenseProperties::DetermineImpactResult()
{
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(GetDefensePropertyOwner());
	if (IsValid(OwnerCharacter))
	{
		AController* OwnerController = OwnerCharacter->GetController();
		UStateManagerComponent* StateComp = OwnerController->GetComponentByClass<UStateManagerComponent>();

		if (IsValid(StateComp))
		{
			UStateBase* BlockHitState = StateComp->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.BlockHit"));
			if (IsValid(BlockHitState) && BlockHitState->CanPerformState())
			{
				SetImpactResult(FGameplayTag::RequestGameplayTag("Impact.Result.Block"));
				return;
			}
		}
	}

	// Default Impact Result
	SetImpactResult(FGameplayTag::RequestGameplayTag("Impact.Result.Hit"));
}

void UDefenseProperties::ApplyImpactHitReactions_Implementation()
{
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(GetDefensePropertyOwner());
	if (IsValid(OwnerCharacter))
	{
		AController* OwnerController = OwnerCharacter->GetController();
		UStateManagerComponent* StateComp = OwnerController->GetComponentByClass<UStateManagerComponent>();

		if (IsValid(StateComp))
		{
			if (ImpactResult == FGameplayTag::RequestGameplayTag("Impact.Result.Hit"))
			{			
				StateComp->TryPerformStateOfClass(StateComp->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Hit"))->GetClass());
				return;
			}

			if (ImpactResult == FGameplayTag::RequestGameplayTag("Impact.Result.Block"))
			{
				StateComp->TryPerformStateOfClass(StateComp->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.BlockHit"))->GetClass());
				return;
			}
		}
	}
}

void UDefenseProperties::ApplyImpactAttributes_Implementation()
{
	if (ImpactResult == FGameplayTag::RequestGameplayTag("Impact.Result.Hit"))
	{
		ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(GetDefensePropertyOwner());
		if (IsValid(OwnerCharacter))
		{
			OwnerCharacter->Health = FMath::Clamp(OwnerCharacter->Health - 10.f, 0, OwnerCharacter->MaxHealth);
			UE_LOG(LogTemp, Warning, TEXT("Character %s, Curr Health: %f"), *OwnerCharacter->GetName(), OwnerCharacter->Health);
			if (OwnerCharacter->ActorGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Character.AI")))
			{
				UEnemyCombatComponent* Combat = OwnerCharacter->GetComponentByClass<UEnemyCombatComponent>();
				ACharacterBase* Target = Cast<ACharacterBase>(Combat->GetCombatTarget());
				APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>(Target->GetController());
				PlayerController->UpdateHUDInfo(GetDefensePropertyOwner());
			}
			else 
			{
				APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>(OwnerCharacter->GetController());
				PlayerController->UpdateHUDInfo(nullptr);
			}		

			if (OwnerCharacter->Health <= 0.f)
			{
				UStateManagerComponent* StateComp = OwnerCharacter->GetController()->GetComponentByClass<UStateManagerComponent>();
				UStateBase* DeathState = StateComp->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Death")));
				StateComp->TryPerformStateOfClass(DeathState->GetClass());				
			}
		}
	}
}

void UDefenseProperties::ApplyHitEffectByClass(TSubclassOf<UImpactEffects> ClassToApply)
{
	UImpactEffects* HitEffect = GetHitEffectByClass(ClassToApply);
	if (IsValid(HitEffect))
	{		
		HitEffect->SetHitResult(OwnerCombatComponent->ReceivedAttackProperty->HitResult);
		HitEffect->ApplyEffect();
	}
	else
	{
		if (IsValid(OwnerCombatComponent->ReceivedAttackProperty))
		{
			UImpactEffects* NewImpactEffect = NewObject<UImpactEffects>(DefensePropertyOwner, ClassToApply);
			CreatedImpactEffects.AddUnique(NewImpactEffect);

			NewImpactEffect->SetHitResult(OwnerCombatComponent->ReceivedAttackProperty->HitResult);
			NewImpactEffect->ApplyEffect();
		}
	}
}

UImpactEffects* UDefenseProperties::GetHitEffectByClass(TSubclassOf<UImpactEffects> ImpactEffect)
{
	if (IsValid(ImpactEffect))
	{
		for (UImpactEffects* CreatedEffect: CreatedImpactEffects)
		{
			if (CreatedEffect->GetClass() == ImpactEffect)
			{
				return CreatedEffect;
			}
		}		
	}
	return nullptr;
}
