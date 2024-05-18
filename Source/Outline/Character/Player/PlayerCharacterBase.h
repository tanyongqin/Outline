// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Interfaces/PlayerInputs.h"
#include "PlayerCharacterBase.generated.h"

class AWeaponBase;
class UAbilityManagerComponent;
class UAttributesComponent;
class UPlayerCombatComponent;
class UTargetingComponent;
class UCameraModeComponent;
 // class UStatisticsComponent;
class UCollisionManagerComponent;

UCLASS()
class OUTLINE_API APlayerCharacterBase : public ACharacterBase, public IPlayerInputs
{
	GENERATED_BODY()
	 
public:
	APlayerCharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeaponBase> WeaponClassToSpawn;
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = Input)
	float TurnRateGameped = 50.f;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilityManagerComponent> AbilityManager;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributesComponent> AttributesComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCombatComponent> CombatComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTargetingComponent> TargetingComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraModeComponent> CameraModeComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCollisionManagerComponent> CollisionManager;

public:

	virtual void UpdateHUDInfo(AActor* ActorToUpdate) override;

	virtual bool DoesInputExistInMapping(FName InputToCheck) override;

	FORCEINLINE UTargetingComponent* GetTargetingComponent() const { return TargetingComponent; }
};
