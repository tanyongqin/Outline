// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "Outline/Interfaces/GeneralInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class OUTLINE_API ACharacterBase : public ACharacter, public IGameplayTagAssetInterface, public IGeneralInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);					
	void OnAttackReceived();

private:
	UPROPERTY()
	class UCombatComponent* LocalCombatComponent;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	FGameplayTagContainer ActorGameplayTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = ActorGameplayTags; }

	float Health;
	float MaxHealth;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE float GetCurrHealth() const { return Health; }
};
