// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackProperties.h"
#include "Outline/Objects/DefenseProperties.h"
#include "Outline/Components/CombatComponent.h"

UAttackProperties::UAttackProperties()
{
}

void UAttackProperties::ProcessAttackPropertry()
{
	if (IsValid(AttackPropertyOwner))
	{
		UDefenseProperties* TargetDefenseProperty = GetHitTargetDefenseProperty();
		if (IsValid(GetHitTargetDefenseProperty()))
		{
			SetImpactResult(TargetDefenseProperty->ImpactResult);
			// SetAttackImpactValues();
		}
	}
}

UDefenseProperties* UAttackProperties::GetHitTargetDefenseProperty() const
{
	UCombatComponent* CombatComp = HitResult.GetActor()->GetComponentByClass<UCombatComponent>();
	if (IsValid(CombatComp))
	{
		return CombatComp->OwnerDefenseProperty;
	}
	return nullptr;
}


