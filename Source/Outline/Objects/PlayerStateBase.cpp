// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Outline/Objects/BufferingBase.h"
#include "Outline/Character/CharacterBase.h"
#include "Outline/Components/AbilityManagerComponent.h"
#include "Outline/Components/TargetingComponent.h"

void UPlayerStateBase::ConstructState()
{
	Super::ConstructState();
	OwnerCharacter = Cast<ACharacterBase>(PerformingActor);
	LocalAbilityManager = OwnerCharacter->GetComponentByClass<UAbilityManagerComponent>();
	LocalTargetingComponent = OwnerCharacter->GetComponentByClass<UTargetingComponent>();
	ReceiveConstructState();
}

void UPlayerStateBase::RemoveAllNoneBufferingObjects()
{

	for (int i = BufferingObjects.Num() - 1; i >=0 ; i--)
	{
		if (BufferingObjects[i]->BufferingState != EInputBufferType::NO_BUFFER)
		{
			RemoveBufferingObject(BufferingObjects[i]);
		}
	}
}

void UPlayerStateBase::ClearStateValues()
{
	Super::ClearStateValues();

	SetBufferedInput(FName(""));
	RemoveAllNoneBufferingObjects();
}

void UPlayerStateBase::ConstructDefaultAllowedInputs(TArray<FName> AllowedInputs)
{
	if (!IsValid(DefaultBufferObject))
	{
		DefaultBufferObject = NewObject<UBufferingBase>(OwnerCharacter);
		DefaultBufferObject->AllowedInputActions = AllowedInputs;
		AddBufferingObject(DefaultBufferObject);
		DefaultBufferObject->SetBufferingState(EInputBufferType::NO_BUFFER);
	}
}

void UPlayerStateBase::ModifyDefaultAllowedInputs(TArray<FName> AllowedInputs)
{
	DefaultBufferObject->AllowedInputActions = AllowedInputs;
}

bool UPlayerStateBase::GetCanAllowStateWithInput(FName InputAction)
{
	for (UBufferingBase* Buffering: BufferingObjects)
	{
		if (Buffering->BufferingState == EInputBufferType::NO_BUFFER && Buffering->AllowedInputActions.Contains(InputAction) )
		{
			return true;
		}
	}
	return false;
}

void UPlayerStateBase::TrySaveAsBufferedInput(FName InputActionToSave)
{
	for (UBufferingBase* Buffering : BufferingObjects)
	{
		Buffering->TrySaveAsInputBuffer(InputActionToSave);
	}
}

void UPlayerStateBase::RotateToTargetedActor(float alpha)
{
	if (IsValid(LocalTargetingComponent) && IsValid(LocalTargetingComponent->GetTargetedActor()))
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), LocalTargetingComponent->GetTargetedActor()->GetActorLocation());
		
		// UKismetMathLibrary::Lerp(Rotator) ?
		// FQuat::Slerp(OwnerCharacter->GetActorRotation().Quaternion(), TargetRotation.Quaternion(), alpha, true);
		FRotator LerpRotation = FMath::Lerp(OwnerCharacter->GetActorRotation(), TargetRotation, alpha);
		FRotator NewRotation = OwnerCharacter->GetActorRotation();
		NewRotation.Yaw = LerpRotation.Yaw;
		OwnerCharacter->SetActorRotation(NewRotation);
	}
}

void UPlayerStateBase::AddBufferingObject(UBufferingBase* NewBufferObject)
{
	BufferingObjects.AddUnique(NewBufferObject);
	NewBufferObject->SetBaseStateToEffect(this);
}
