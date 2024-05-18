// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInputs.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPlayerInputs : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OUTLINE_API IPlayerInputs
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual bool DoesInputExistInMapping(FName InputToCheck);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual FName GetLastFireInput();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void SetLastFireInput(FName NewLastFiredInput);

	UFUNCTION(BlueprintCallable, Category = "Movement Inputs")
	virtual FVector GetDirectionFromMovementInputs();

};
