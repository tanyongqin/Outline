// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "DefenseProperties.generated.h"

class UCombatComponent;
class UImpactEffects;

UCLASS()
class OUTLINE_API UDefenseProperties : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UCombatComponent* OwnerCombatComponent;

	UPROPERTY()
	TArray<UImpactEffects*> CreatedImpactEffects;
public:

	UPROPERTY()
	AActor* DefensePropertyOwner;

	UPROPERTY(BlueprintReadOnly, Category = "Base Variables")
	FGameplayTag ImpactResult;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Functions")
	AActor* GetDefensePropertyOwner() { return DefensePropertyOwner; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetDefensePropertyOwner(AActor* NewOwner) { DefensePropertyOwner = NewOwner; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void ConstructDefenseProperty();

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void ProcessReceivedAttack();

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetImpactResult(FGameplayTag NewImpactResult) { ImpactResult = NewImpactResult; }

public:

	UFUNCTION(BlueprintCallable, Category = "DefenseProperties | Functions")
	void DetermineImpactResult();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DefenseProperties | Functions")
	void ApplyImpactHitReactions();
	virtual void ApplyImpactHitReactions_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DefenseProperties | Functions")
	void ApplyImpactAttributes();
	virtual void ApplyImpactAttributes_Implementation();

	UFUNCTION(BlueprintCallable, Category = "DefenseProperties | Effect Functions")
	void ApplyHitEffectByClass(TSubclassOf<UImpactEffects> ClassToApply);

	UFUNCTION(BlueprintCallable, Category = "DefenseProperties | Effect Functions")
	UImpactEffects* GetHitEffectByClass(TSubclassOf<UImpactEffects> ImpactEffect);
};
