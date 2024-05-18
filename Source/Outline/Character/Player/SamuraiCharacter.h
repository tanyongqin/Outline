// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterBase.h"
#include "SamuraiCharacter.generated.h"

UCLASS()
class OUTLINE_API ASamuraiCharacter : public APlayerCharacterBase
{
	GENERATED_BODY()
	
public:
	ASamuraiCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// From Character Base
	// virtual void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

};
