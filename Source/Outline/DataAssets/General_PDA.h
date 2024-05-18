// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "General_PDA.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class OUTLINE_API UGeneral_PDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Attributes")
	TArray<class UAttributeBase*> AttributesToCreate;
};
