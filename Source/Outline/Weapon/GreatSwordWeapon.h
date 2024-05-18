// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyWeaponBase.h"
#include "GreatSwordWeapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class OUTLINE_API AGreatSwordWeapon : public AEnemyWeaponBase
{
	GENERATED_BODY()
	
public:
	AGreatSwordWeapon();

	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* WeaponMeshComponent;

	virtual void EquipWeapon_Implementation() override;
	virtual void UnEquipWeapon_Implementation() override;

protected:
	virtual void BeginPlay() override;
};
