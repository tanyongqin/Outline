// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "StateBase.generated.h"

class UStateManagerComponent;
class UAbilityBase;

UCLASS(Blueprintable, BlueprintType)
class OUTLINE_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:
	UStateBase();

	// 状态对应的标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Properties")
	FGameplayTag StateGameplayTag;

	// 启用: 当计时器到达时, 发生指定时间, 配合下面两个属性使用
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Properties")
	bool bTimeControlledState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Controls", meta = (EditCondition = "bTimeControlledState"))
	float StateTimeLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Controls", meta = (EditCondition = "bTimeControlledState"))
	float TimerUpdateRate = 0.1f;

	FTimerHandle PassedTimerHandle;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "State Time")
	float TimePassed;

	UPROPERTY()
	AActor* PerformingActor;

private:
	UPROPERTY()
	UStateManagerComponent* OwnerStateManager;

	UPROPERTY()
	TSubclassOf<UAbilityBase> SelectedAbilityToTrigger;
public:

	/* State Main Events */
	virtual void ConstructState();

	UFUNCTION(BlueprintImplementableEvent, Category = "State Base Events", meta = (DisplayName = "Construct State"))
	void ReceiveConstructState();

	UFUNCTION(BlueprintCallable, Category = "State Base Events")
	virtual void StartState();

	UFUNCTION(BlueprintImplementableEvent, Category = "State Base Events", meta = (DisplayName = "Start State"))
	void ReceiveStartState();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State Base Events")
	void TickState(float TickTime);

	UFUNCTION(BlueprintCallable, Category = "State Base Events")
	virtual void EndState();

	UFUNCTION(BlueprintImplementableEvent, Category = "State Base Events", meta = (DisplayName = "End State"))
	void ReceiveEndState();

	UFUNCTION(BlueprintCallable, Category = "State Base Events")
	virtual bool RestartState(bool ConditionCheck);


	/* State Main Functions */
	UFUNCTION(BlueprintCallable, Category = "State Base Functions")
	virtual void ClearStateValues();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "State Base Functions")
	void PrepareStateValues();
	virtual void PrepareStateValues_Implementation();

	UFUNCTION(BlueprintCallable, Category = "State Base Functions")
	virtual void StartStateTimer();

	UFUNCTION(BlueprintCallable, Category = "State Base Functions")
	virtual void IncrementPassedTime();

	UFUNCTION(BlueprintCallable, Category = "State Base Functions")
	virtual void ClearPassedTime();

	UFUNCTION(BlueprintCallable, Category = "State Base Functions")
	virtual void StopStateTimer();

	UFUNCTION(BlueprintCallable, Category = "State Base Functions")
	virtual float IncrementTimeByUpdateRate();

	/* State Setters */
	UFUNCTION(BlueprintCallable, Category = "State Setters")
	void SetPerformingActor(AActor* NewPerformingActor) { PerformingActor = NewPerformingActor; }

	// this function gets called when the developer calls the “Try Perfrom Ability Of Class”
	//  from the state manager component. if you have the condition set to true, this function will get called.
	/* State Getters */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure, Category = "State Getters")
	bool CanPerformState();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Getters")
	bool CanSetAsQueueState();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Getters")
	void GetPerformingActor(AActor*& CurrentPerformingActor) { CurrentPerformingActor = PerformingActor; }

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "State Getters")
	float GetTimePassed() { return TimePassed; }

public:

	UFUNCTION(BlueprintCallable, Category = "State Functions")
	bool CheckAbilitiesToRun(TArray<TSubclassOf<UAbilityBase>> AbilitiesToCheck);

	UFUNCTION(BlueprintCallable, Category = "State Getters")
	FORCEINLINE UStateManagerComponent* GetStateManagerComponent() const { return OwnerStateManager; }

	UFUNCTION(BlueprintCallable, Category = "State Getters")
	FORCEINLINE TSubclassOf<UAbilityBase> GetSelectedAbility() const { return SelectedAbilityToTrigger; }
};
