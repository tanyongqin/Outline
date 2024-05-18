// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputs.h"

// Add default functionality here for any IPlayerInputs functions that are not pure virtual.

bool IPlayerInputs::DoesInputExistInMapping(FName InputToCheck)
{

	return false;
}

FName IPlayerInputs::GetLastFireInput()
{
	return FName();
}

void IPlayerInputs::SetLastFireInput(FName NewLastFiredInput)
{
}

FVector IPlayerInputs::GetDirectionFromMovementInputs()
{
	return FVector();
}
