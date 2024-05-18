// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "AttributeBase.generated.h"

USTRUCT(BlueprintType)
struct FAttributeProperties
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Properties")
	float AttributeValue = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Properties")
	float CurrAttributeValue = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Properties")
	float MinAttributeValue = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attribute Properties")
	float MaxAttributeValue = 0.f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueUpdated, FGameplayTag, UpdatedValue);

UCLASS()
class OUTLINE_API UAttributeBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Base Dispatchers")
	FOnValueUpdated OnValueUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Properties", meta = (ExposeOnSpawn = true))
	FAttributeProperties AttributeValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Properties", meta = (ExposeOnSpawn = true))
	FGameplayTag AttributeGameplayTag;

protected:
	UPROPERTY()
	AActor* OwningActor;

public:
	/* Attribute Main Functions */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attribute Base Functions")
	void ConstructAttribute();

	UFUNCTION(BlueprintCallable, Category = "Attribute Base Functions")
	void ModifyAttribute(float ModifyBy);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attribute Base Functions")
	void TickAttribute(float TickTime);


	UFUNCTION(BlueprintCallable, Category = "Attribute Setters")
	void SetOwningActor(AActor* NewOwningActor) { OwningActor = NewOwningActor; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attribute Getters")
	void GetOwningActor(AActor*& CurrentOwningActor) { CurrentOwningActor = OwningActor; }
};
