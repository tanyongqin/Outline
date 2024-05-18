// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "AttributeModifier.generated.h"

USTRUCT(BlueprintType)
struct FAttributeModifierProperties
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Modifier Properties", meta = (ExposeOnSpawn))
	FGameplayTag AttributeToModify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Modifier Properties")
	bool bIndefinite = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Modifier Properties", meta = (EditCondition = "!bIndefinite", EditConditionHides))
	float ModificationDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Modifier Properties")
	float ModificationInterval = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Modifier Properties")
	float AmountToAdd = 1.f;

};

UCLASS(BlueprintType, Blueprintable)
class OUTLINE_API UAttributeModifier : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Attribute Modifier Initialization")
	FAttributeModifierProperties ModiferProperties;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attribute Modifier Base Functions")
	void ConstructAttributeModifier();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attribute Modifier Base Functions")
	void StartAttributeModifier();

};
