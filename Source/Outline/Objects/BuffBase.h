// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuffBase.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UBuffBase : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	AActor* DamageDealer;

	UPROPERTY()
	AActor* DamageReceiver;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Functions")
	AActor* GetDamageDealer() { return DamageDealer; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Functions")
	AActor* GetDamageReceiver() { return DamageReceiver; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetDamageDealer(AActor* NewDamageDealer) { DamageDealer = NewDamageDealer; }

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetDamageReceiver(AActor* NewDamageReceiver) { DamageReceiver = NewDamageReceiver; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void StartBuff();
};
