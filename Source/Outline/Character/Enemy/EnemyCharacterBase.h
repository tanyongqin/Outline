// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "Outline/Interfaces/TargetingSystemInterface.h"
#include "EnemyCharacterBase.generated.h"

class UAbilityManagerComponent;
class UAttributesComponent;
class UEnemyCombatComponent;
class UCollisionManagerComponent;
class UBaseEnemy_PDA;
class AEnemySpawner;
class AEnemyControllerBase;

USTRUCT(BlueprintType)
struct FSpawnProperties
{
	GENERATED_BODY()

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEnemySpawner> Spawner;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation = FVector(0);
};

UCLASS()
class OUTLINE_API AEnemyCharacterBase : public ACharacterBase, public ITargetingSystemInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization", Meta = (ExposeOnSpawn = true))
	UBaseEnemy_PDA* AssociatedDataAsset;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	AEnemyControllerBase* MyController;

private:

	UPROPERTY(EditAnywhere)
	FSpawnProperties SpawnProperties;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilityManagerComponent> AbilityManager;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributesComponent> AttributesComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyCombatComponent> CombatComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCollisionManagerComponent> CollisionManager;

public:
	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE FSpawnProperties GetSpawnProperties() const { return SpawnProperties; }

	FORCEINLINE UAbilityManagerComponent* GetAbilityComponent() const { return AbilityManager; }

	FORCEINLINE UAttributesComponent* GetAttributesComponent() const { return AttributesComponent; }

	FORCEINLINE UEnemyCombatComponent* GetCombatComponent() const { return CombatComponent; }

	FORCEINLINE UCollisionManagerComponent* GetCollisionComponent() const { return CollisionManager; }
};
