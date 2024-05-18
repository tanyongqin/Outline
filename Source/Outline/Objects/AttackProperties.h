// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "AttackProperties.generated.h"

class UDefenseProperties;

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class OUTLINE_API UAttackProperties : public UObject
{
	GENERATED_BODY()
	
public:
	UAttackProperties();

	UPROPERTY()
	AActor* AttackPropertyOwner;

	UPROPERTY()
	FHitResult HitResult;

	UPROPERTY()
	FGameplayTag ImpactResult;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Functions")
	AActor* GetAttackPropertyOwner() { return AttackPropertyOwner; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetAttackPropertyOwner(AActor* NewAttacker) { AttackPropertyOwner = NewAttacker; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Functions")
	FHitResult GetHitResult() { return HitResult; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetHitResult(FHitResult NewHitResult) { HitResult = NewHitResult; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Functions")
	FGameplayTag GetImpactResult() { return ImpactResult; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetImpactResult(FGameplayTag NewImpactResult) { ImpactResult = NewImpactResult; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void ConstructAttackPropertry();

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void ProcessAttackPropertry();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AttackProperties | Functions")
	UDefenseProperties* GetHitTargetDefenseProperty() const;
};
