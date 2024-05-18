// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyControllerBase.generated.h"

class UStateManagerComponent;
class AEnemyCharacterBase;

UCLASS()
class OUTLINE_API AEnemyControllerBase : public AAIController 
{
	GENERATED_BODY()
	
public:
	AEnemyControllerBase();

	void InitializeAIController();

	UFUNCTION()
	void ReceiveAbilityUpdate();
	
	UFUNCTION()
	void ReceiveStateUpdate();

	UFUNCTION()
	void ReceiveTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateManagerComponent> OwnerStateComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerception;

	UPROPERTY()
	AEnemyCharacterBase* OwnerCharacter;
};
