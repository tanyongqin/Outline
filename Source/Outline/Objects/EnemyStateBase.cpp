// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStateBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Outline/Character/Enemy/EnemyCharacterBase.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/EnemyCombatComponent.h"


void UEnemyStateBase::ConstructState()
{
	Super::ConstructState();
	
	if (IsValid(PerformingActor))
	{
		OwnerCharacter = Cast<AEnemyCharacterBase>(PerformingActor);
		OwnerController = Cast<AEnemyControllerBase>(OwnerCharacter->GetController());
	}
	ReceiveConstructState();
}

void UEnemyStateBase::StartStateTimer()
{
	if (bTimeControlledState) 
	{
		GetWorld()->GetTimerManager().SetTimer(PassedTimerHandle, this, &UStateBase::IncrementPassedTime, TimerUpdateRate, true, 0.f);
	}
	
}

void UEnemyStateBase::IncrementPassedTime()
{
	if (GetStateManagerComponent())
	{
		UStateBase* CurrrentActiveState = GetStateManagerComponent()->GetCurrentActiveState();
		if (IsValid(CurrrentActiveState) && CurrrentActiveState == this)
		{
			IncrementTimeByUpdateRate();

			// 到时间, 清除
			if (TimePassed >= StateTimeLimit)
			{
				ClearPassedTime();
				DecideNextState();
			}
		}
		else
		{
			EndState();
		}
	}
}

void UEnemyStateBase::DecideNextState_Implementation()
{
	EndState();
}

float UEnemyStateBase::CalcDistance()
{
	UEnemyCombatComponent* Combat = OwnerCharacter->GetCombatComponent();
	if (IsValid(Combat->GetCombatTarget()))
	{
		return (Combat->GetCombatTarget()->GetActorLocation() - OwnerCharacter->GetActorLocation()).Length();
	}
	return 0.0f;
}

FRotator UEnemyStateBase::CalcYawAndPitch()
{
	UEnemyCombatComponent* Combat = OwnerCharacter->GetCombatComponent();
	if (IsValid(Combat->GetCombatTarget()))
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			OwnerCharacter->GetActorLocation(), 
			Combat->GetCombatTarget()->GetActorLocation()
		);
		FRotator SmoothedRotation = FMath::Lerp(OwnerCharacter->GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds);
		SmoothedRotation.Roll = 0.f;
		return SmoothedRotation;
	}
	return FRotator();
}
