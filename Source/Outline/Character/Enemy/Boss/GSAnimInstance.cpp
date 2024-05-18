// Fill out your copyright notice in the Description page of Project Settings.


#include "GSAnimInstance.h"
#include "GSCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

void UGSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AGSCharacter>(TryGetPawnOwner());
}

void UGSAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Character == nullptr)
	{
		Character = Cast<AGSCharacter>(TryGetPawnOwner());
	}

	if (Character == nullptr) return;

	FVector Velocity = Character->GetVelocity();

	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = Character->GetCharacterMovement()->IsFalling();
	bIsAccelerating = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	bIsDie = Character->Health <= 0.f ? true : false;
}

