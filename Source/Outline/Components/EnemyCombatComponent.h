// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UEnemyCombatComponent : public UCombatComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<AActor*> CombatTargets;

public:
	UFUNCTION(BlueprintCallable, Category = "Getters")
	AActor* GetCombatTarget();

	UFUNCTION(BlueprintCallable, Category = "Exiting Combat")
	void ClearCombatTargets();

	UFUNCTION(BlueprintCallable, Category = "Entering Combat")
	void AddCombatTarget(AActor* TargetToAdd);

	UFUNCTION(BlueprintCallable, Category = "Entering Combat")
	void SetCombatTarget(AActor* NewCombatTarget);

	UFUNCTION(BlueprintCallable, Category = "Entering Combat")
	void EnterCombat();

	UFUNCTION(BlueprintCallable, Category = "Exiting Combat")
	void ExitCombat();

	UFUNCTION(BlueprintCallable)
	void RotateEnemyToCombatTarget(float RotateSpeed = 0.05);
};
