// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "ConditionBase.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UConditionBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition Properties")
	FGameplayTag ConditionGameplayTag;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Condition Base Functions")
	bool GetConditionResult();
};
