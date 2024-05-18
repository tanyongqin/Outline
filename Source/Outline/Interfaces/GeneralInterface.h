// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Outline/GameTypes/Moveset.h"
#include "GeneralInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UGeneralInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OUTLINE_API IGeneralInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, Category = "Controller")
	virtual void InitializeController();
	
	UFUNCTION(BlueprintCallable)
	virtual void AssignMoveset(EMoveset NewMoveset);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateHUDInfo(AActor* ActorToUpdate);

};
