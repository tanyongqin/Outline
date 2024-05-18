// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Outline/Objects/AttributeModifier.h"
#include "AttributesComponent.generated.h"

class UAttributeBase;
class UAttributeModifier;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OUTLINE_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributesComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute Base Variables")
	TArray<UAttributeBase*> CreatedAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute Base Variables")
	TArray<UAttributeModifier*> CreatedActiveAttributeModifiers;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization Functions")
	void InitializeAttributesComponent(const TArray<TSubclassOf<UAttributeBase>>& NewAttributesToCreate);
	virtual void InitializeAttributesComponent_Implementation(const TArray<TSubclassOf<UAttributeBase>>& NewAttributesToCreate);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AssignAttributes(TArray<UAttributeBase*> AttributesToAssign);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ClearAttributes();

	/* Construction */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ConstructAttributeOfClass(TSubclassOf<UAttributeBase> AttributeToConstruct, UAttributeBase*& ConstructedAttribute);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ConstructAttributeModifierOfClass(TSubclassOf<UAttributeModifier> AttributeModifierToConstruct, FAttributeModifierProperties ModiferProperties, UAttributeModifier*& ConstructedAttributeModifier);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetAttributeOfClass(TSubclassOf<UAttributeBase> AttributeToSearch, UAttributeBase*& FoundAttribute);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetActiveAttributeModifierOfClass(TSubclassOf<UAttributeModifier> AttributeModifierToSearch, UAttributeModifier*& FoundAttributeModifier);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UAttributeBase* GetAttributeOfGameplayTag(FGameplayTag AttributeGameplayTag);


	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RemoveFromActiveAttributeModifiers(UAttributeModifier* AttributeModifierToRemove);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AddToActiveAttributeModifiers(UAttributeModifier* AttributeModifierToAdd);

};
