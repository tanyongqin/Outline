// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

FRotator UGeneralBlueprintFunctionLibrary::CalculateAngle(AActor* Start, AActor* Target)
{
	if (IsValid(Start) && IsValid(Target))
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start->GetActorLocation(), Target->GetActorLocation());
		FRotator Delta = Start->GetActorRotation() - TargetRotation;
		Delta.Normalize();
		return Delta;
	}
	return FRotator();
}
