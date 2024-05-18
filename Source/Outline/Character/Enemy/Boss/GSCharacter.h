// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyCharacterBase.h"
#include "GSCharacter.generated.h"

UENUM(BlueprintType)
enum class GSState : uint8
{
	GSS_IDLE UMETA(DisplayName = "Idle"),					// Outside of combat
	GSS_OBSERVE UMETA(DisplayName = "Observe"),				// Observe the player
	GSS_ATTACK UMETA(DisplayName = "Attack"),				// In the process of attacking
	GSS_GUARD UMETA(DisplayName = "Guard"),					// In Guard State
	GSS_STUMBLE UMETA(DisplayName = "Stumble"),				// Stumbling from being damaged/interrupted
	GSS_TAUNT UMETA(DisplayName = "Taunt"),					// Emoting during a fight
	GSS_DEAD UMETA(DisplayName = "Dead"),					// Dead
	GSS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class DistanceType : uint8
{
	DT_NEAR UMETA(DisplayName = "Near"),				
	DT_CLOSE UMETA(DisplayName = "Close"),				
	DT_MID UMETA(DisplayName = "Mid"),				
	DT_FAR UMETA(DisplayName = "Far"),					
	GSS_MAX UMETA(DisplayName = "DefaultMax")
};

class AWeaponBase;

UCLASS()
class OUTLINE_API AGSCharacter : public AEnemyCharacterBase
{
	GENERATED_BODY()
	
public:
	AGSCharacter();
	void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponClassToSpawn;
};
