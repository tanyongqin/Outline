// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TraceBase.h"
#include "TraceAOE.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UTraceAOE : public UTraceBase
{
	GENERATED_BODY()
	
private:
	float Radius = 150.f;

public:

	virtual void DoCollisionTrace_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Setters")
	FORCEINLINE void SetRadius(float NewRadius) { Radius = NewRadius; }

	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE float GetRadius() const { return Radius; }
};
