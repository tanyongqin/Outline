// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyControllerBase.h"
#include "GSAIController.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API AGSAIController : public AEnemyControllerBase
{
	GENERATED_BODY()


protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};
