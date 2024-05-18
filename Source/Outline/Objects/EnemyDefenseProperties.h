// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefenseProperties.h"
#include "EnemyDefenseProperties.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UEnemyDefenseProperties : public UDefenseProperties
{
	GENERATED_BODY()
	
public:

	virtual void ApplyImpactHitReactions_Implementation() override;
};
