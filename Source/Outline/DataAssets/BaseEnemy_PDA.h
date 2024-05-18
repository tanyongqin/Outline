// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General_PDA.h"
#include "Outline/GameTypes/AbilityMontages.h"
#include "BaseEnemy_PDA.generated.h"

class AAIController;
class UBehaviorTree;
class UEnemyStateBase;

UCLASS()
class OUTLINE_API UBaseEnemy_PDA : public UGeneral_PDA
{
	GENERATED_BODY()
	
public:
	// ------------------------------------------------
	// Base Properties
	// ------------------------------------------------
	UPROPERTY(EditAnyWhere, Category = "Base Properties")
	FName EnemyName;

	UPROPERTY(EditAnyWhere, Category = "Base Properties")
	TSubclassOf<AAIController> EnemyController;

	// ------------------------------------------------
	// Behaviour Tree
	// ------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Behavior Tree Info")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree Info")
	TMap<FGameplayTag, FName> BTKeys;

	// ------------------------------------------------
	// States Properties
	// ------------------------------------------------

	UPROPERTY(EditAnywhere, Category = "States Properties")
	TSubclassOf<UEnemyStateBase> OnSpawnState;

	UPROPERTY(EditAnywhere, Category = "States Properties")
	TSubclassOf<UEnemyStateBase> OnSeenState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States Properties")
	TArray<TSubclassOf<UEnemyStateBase>> AvailableEnemyStates;

	// ------------------------------------------------
	// Anim Montage
	// ------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Montages")
	TArray<FAbilityMontages> Abilities;
};
