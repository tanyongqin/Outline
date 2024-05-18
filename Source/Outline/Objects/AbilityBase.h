// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "AbilityBase.generated.h"

class UAbilityManagerComponent;

UCLASS(Blueprintable)
class OUTLINE_API UAbilityBase : public UObject
{
	GENERATED_BODY()
	
public:
	UAbilityBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Properties")
	FGameplayTag AbilityGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Properties")
	bool bHasCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Controls", meta = (EditCondition = "bHasCooldown"))
	float CooldownDuration = 0.f;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Ability Properties")
	class UAnimMontage* ActiveAbilityMontage;

	UPROPERTY()
	AActor* PerformingActor;

	UPROPERTY(BlueprintReadWrite, Category = "Cooldown")
	bool bAbilityOnCooldown;

private:
	UPROPERTY()
	UAbilityManagerComponent* OwnerAbilityComponent;

public:
	/* Ability Main Functions */
	UFUNCTION(BlueprintCallable, Category = "Ability Base Functions")
	void ConstructAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability Base Functions", DisplayName = "Construct Ability")
	void ReceiveConstructAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability Base Functions", DisplayName = "Start Ability")
	void ReceiveStartAbility();

	UFUNCTION(BlueprintCallable, Category = "Ability Base Functions")
	void StartAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability Base Functions")
	void TickAbility(float TickTime);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability Base Functions", DisplayName = "End Ability")
	void ReceiveEndAbility();

	UFUNCTION(BlueprintCallable, Category = "Ability Base Functions")
	void EndAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability Base Functions")
	void InterruptAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability Base Functions")
	void CancelAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability Base Functions")
	void ApplyAbilityCooldown();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability Base Functions")
	void CooldownReset();

	/* Ability Getters */
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable, Category = "Ability Getters")
	bool CanPerformAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable, Category = "Ability Getters")
	bool CanRePerformAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable, Category = "Ability Getters")
	bool CanIntteruptAbility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable, Category = "Ability Getters")
	bool CanAbilityBeCanceled();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable, Category = "Ability Getters")
	bool GetIsAbilityOnCooldown();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Getters")
	void GetPerformingActor(AActor*& CurrentPerformingActor) { CurrentPerformingActor = PerformingActor; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Getters")
	void GetActiveAbilityMontage(UAnimMontage*& CurrentActiveMontage) { CurrentActiveMontage = ActiveAbilityMontage; }

	/* Ability Setters */
	UFUNCTION(BlueprintCallable, Category = "Ability Setters")
	void SetActiveAbilityMontage(UAnimMontage* NewActiveMontage) { ActiveAbilityMontage = NewActiveMontage; }

	UFUNCTION(BlueprintCallable, Category = "Ability Setters")
	void SetPerformingActor(AActor* NewPerformingActor) { PerformingActor = NewPerformingActor; }

public:
	UFUNCTION(BlueprintCallable, Category = "Ability Functions")
	bool GetIsCurrentAbilityActive();

	UFUNCTION(BlueprintCallable, Category = "Ability Getters")
	FORCEINLINE UAbilityManagerComponent* GetOwnerAbilityComponent() const { return OwnerAbilityComponent; }

	UFUNCTION(BlueprintCallable, Category = "Ability Functions")
	float PlayAbilityMontage(UAnimMontage* MontageToPlay, float InPlayRate, EMontagePlayReturnType ReturnValueType, float InTimeToStartMontageAt, bool bStopAllMontages, FName StartSectionName);
};
