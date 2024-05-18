// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "EnemyStateBase.generated.h"

class AEnemyCharacterBase;
class AEnemyControllerBase;

UCLASS()
class OUTLINE_API UEnemyStateBase : public UStateBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	AEnemyCharacterBase* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	AEnemyControllerBase* OwnerController;

public:
	virtual void ConstructState() override;

	virtual void StartStateTimer() override;

	virtual void IncrementPassedTime() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Utils Function")
	void DecideNextState();
	virtual void DecideNextState_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Utils Function")
	float CalcDistance();

	UFUNCTION(BlueprintCallable, Category = "Utils Function")
	FRotator CalcYawAndPitch();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ProcessCalculations();
};
