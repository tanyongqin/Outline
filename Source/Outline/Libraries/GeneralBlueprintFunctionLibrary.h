// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralBlueprintFunctionLibrary.generated.h"


UCLASS()
class OUTLINE_API UGeneralBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "General Functions")
	static FRotator CalculateAngle(AActor* Start, AActor* Target);

};
