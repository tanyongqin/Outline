// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum class EModifyingType : uint8
{
	Add			UMETA(DisplayName = "Add"),
	Remove		UMETA(DisplayName = "Remove"),

};

class AWeaponBase;
class UBuffBase;
class UConditionBase;
class UAttackProperties;
class UDefenseProperties;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class OUTLINE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tempest Combat Status")
	FGameplayTagContainer CombatStatusContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tempest Combat Buffs")
	TArray<UBuffBase*> AppliedBuffs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tempest Combat Conditions")
	TArray<UConditionBase*> CombatConditions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tempest Combat Properties")
	UDefenseProperties* OwnerDefenseProperty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tempest Combat Properties")
	UAttackProperties* OwnerAttackProperty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tempest Combat Properties")
	UAttackProperties* ReceivedAttackProperty;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AWeaponBase* EquippedWeapon;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void ModifyCombatStatus(FGameplayTag CombatStatusToModify, EModifyingType ModifyType);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat Status Getters")
	FGameplayTagContainer GetCombatStatus() { return CombatStatusContainer; }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void AddToAppliedBuffs(UBuffBase* BuffToAdd) { AppliedBuffs.AddUnique(BuffToAdd); }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void RemoveFromAppliedBuffs(UBuffBase* BuffToRemove) { AppliedBuffs.Remove(BuffToRemove); }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void SetReceivedAttackProperty(UAttackProperties* NewAttackProperty) { ReceivedAttackProperty = NewAttackProperty; }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void SetAttackProperty(UAttackProperties* NewAttackProperty) { OwnerAttackProperty = NewAttackProperty; }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void SetDefenseProperty(UDefenseProperties* NewDefenseProperty) { OwnerDefenseProperty = NewDefenseProperty; }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void AddToCombatConditions(UConditionBase* ConditionToAdd) { CombatConditions.AddUnique(ConditionToAdd); }

	UFUNCTION(BlueprintCallable, Category = "Combat Status Setters")
	void RemoveFromCombatConditions(UConditionBase* ConditionToRemove) { CombatConditions.Remove(ConditionToRemove); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat Condition Getters")
	UConditionBase* GetCombatConditionOfGameplayTag(FGameplayTag ConditionGameplayTag);

	/* Construction */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ConstructDefensePropertyOfClass(TSubclassOf<UDefenseProperties> PropertyToConstruct, UDefenseProperties*& ConstructedProperty);

	UFUNCTION(BlueprintCallable, Category = "Weapon Setters")
	void SetEquippedWeapon(AWeaponBase* NewEquippedWeapon) { EquippedWeapon = NewEquippedWeapon; }
		
	UFUNCTION(BlueprintCallable, Category = "Weapon Getters")
	FORCEINLINE AWeaponBase* GetEquippedWeapon() const { return EquippedWeapon; }
};
