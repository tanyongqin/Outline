// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Outline/Objects/AbilityBase.h"
#include "GameplayTagContainer.h"
#include "AbilityManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedActiveAbility);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTLINE_API UAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityManagerComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Base Dispatchers")
	FOnUpdatedActiveAbility OnUpdatedActiveAbility;

	UPROPERTY(VisibleAnywhere, Category = "Base Variables")
	UAbilityBase* CurrentActiveAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UAbilityBase*> PassiveAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UAbilityBase*> ActivatableAbilities;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization Functions")
	void InitializeAbilitySystemComponent();
	virtual void InitializeAbilitySystemComponent_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Performing Ability")
	void PerformAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSet);

	UFUNCTION(BlueprintCallable, Category = "Performing Ability")
	bool TryPerformAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSet, bool ConditionCheck = true);

	UFUNCTION(BlueprintCallable, Category = "Performing Ability")
	bool TryPerformAbilitiesOfClass(TArray <TSubclassOf<UAbilityBase>> AbilitiesToSet, bool ConditionCheck = true);

	UFUNCTION(BlueprintCallable, Category = "Performing Ability")
	void SetCurrentActiveAbility(UAbilityBase* NewCurrentActiveAbility);

	UFUNCTION(BlueprintCallable, Category = "Performing Ability")
	void SetAsPassiveAbility(UAbilityBase* NewPassiveAbility);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Performing Ability")
	void EndAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToEnd, bool bInterrupt);

	UFUNCTION(BlueprintCallable, Category = "Performing Ability")
	void RemoveFromPassiveAbilities(UAbilityBase* AbilityToRemove) { PassiveAbilities.Remove(AbilityToRemove); }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Performing Ability")
	void ResetAbilityComponent();




	/* Getters */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UAbilityBase* GetCurrentActiveAbility();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSearch, UAbilityBase*& FoundAbility);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	bool GetCanPerformAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSearch);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetPassiveAbilities(TArray<UAbilityBase*>& PassiveAbilitiesArray) { PassiveAbilitiesArray = PassiveAbilities; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetActivatableAbilities(TArray<UAbilityBase*>& ActivatableAbilitiesArray) { ActivatableAbilitiesArray = ActivatableAbilities; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetChildAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToSearch, UAbilityBase*& FoundAbility);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UAbilityBase* GetAbilityOfGameplayTag(FGameplayTag AbilityGameplayTag);



	/* Construction */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ConstructAbilityOfClass(TSubclassOf<UAbilityBase> AbilityToConstruct, UAbilityBase*& ConstructedAbility);

	/* Clears All The Arrays Associated For Finding and Setting Abilities*/
	UFUNCTION(BlueprintCallable, Category = "Clear")
	void ClearAbilityComponent() { PassiveAbilities.Empty(); ActivatableAbilities.Empty(); CurrentActiveAbility = nullptr; }

};
