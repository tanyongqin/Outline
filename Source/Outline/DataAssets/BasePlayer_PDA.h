// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General_PDA.h"
#include "Outline/GameTypes/AbilityMontages.h"
#include "Outline/Objects/PlayerStateBase.h"
#include "GameplayTagContainer.h"
#include "BasePlayer_PDA.generated.h"


UCLASS()
class OUTLINE_API UBasePlayer_PDA : public UGeneral_PDA
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TArray<FName> PlayerInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Montages")
	TArray<FAbilityMontages> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TArray<TSubclassOf<UPlayerStateBase>> StatesToCreate;
};
