// Fill out your copyright notice in the Description page of Project Settings.


#include "SamuraiAnimInstance.h"
#include "PlayerCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Outline/Components/TargetingComponent.h"

void USamuraiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<APlayerCharacterBase>(TryGetPawnOwner());
}

void USamuraiAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OwnerCharacter == nullptr)
	{
		OwnerCharacter = Cast<APlayerCharacterBase>(TryGetPawnOwner());
	}

	if (OwnerCharacter == nullptr) return;

	FVector Velocity = OwnerCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = OwnerCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	FRotator AimRotation = OwnerCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(OwnerCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = OwnerCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	// 限制在这个范围，那么鼠标移动很快，也无法超出范围
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	
	bIsLockon = IsValid(OwnerCharacter->GetTargetingComponent()->TargetedActor);
}
