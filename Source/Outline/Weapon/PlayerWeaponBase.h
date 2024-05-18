// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "PlayerWeaponBase.generated.h"

class UStateMangerComponent;
class UBasePlayer_PDA;

UCLASS()
class OUTLINE_API APlayerWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	UBasePlayer_PDA* AssociatedDataAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void EquipWeapon_Implementation() override;

	virtual void UnEquipWeapon_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Player Weapon Base Functions")
	virtual void SetAttributesAndStates();
};
