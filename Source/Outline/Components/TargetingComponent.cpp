// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Outline/Objects/CameraModeBase.h"
#include "Outline/Character/Enemy/EnemyCharacterBase.h"
#include "Outline/Components/CameraModeComponent.h"
#include "Outline/Components/CombatComponent.h"
#include "Outline/Character/CharacterBase.h"

UTargetingComponent::UTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdatePotentialTargets();

	// If target not in around, disable lock
	if (IsValid(TargetedActor) && !PotentialTargets.Contains(TargetedActor))
	{
		DisableLockOn();
	}
}


void UTargetingComponent::InitializeTargetingComponent_Implementation(UCameraComponent* CameraComponent, USpringArmComponent* SpringArmComponent)
{
	OwnerCamera = CameraComponent;
	OwnerSpringArm = SpringArmComponent;
	LocalCharacter = Cast<ACharacterBase>(GetOwner());
	LocalCameraModeComponent = GetOwner()->GetComponentByClass<UCameraModeComponent>();
	LocalCombatComponent = GetOwner()->GetComponentByClass<UCombatComponent>();
}

void UTargetingComponent::SearchForActorToTarget()
{
	UpdatePotentialTargets();
	InternalSearchForActorToTarget();
}

void UTargetingComponent::InternalSearchForActorToTarget()
{
	if (TargetedActor)
	{
		DisableLockOn();
	}
	else
	{
		TMap<AActor*, float> LocalPotentialTargets;

		for (AActor* Elem : PotentialTargets)
		{
			if (CanBeTargeted(Elem))
			{
				LocalPotentialTargets.Add(Elem, UKismetMathLibrary::Abs(CalculateAngleFromCamera(Elem)));
			}
		}

		if (LocalPotentialTargets.Num() > 0)
		{
			TArray<AActor*> LocalTargets;
			TArray<float> LocalAngles;
			LocalPotentialTargets.GenerateKeyArray(LocalTargets);
			LocalPotentialTargets.GenerateValueArray(LocalAngles);

			int32 MinIndex;
			const float MinValue = FMath::Min<float>(LocalAngles, &MinIndex);
			TargetedActor = LocalTargets[MinIndex];
			SetLockOnToTarget();
		}
	}
}

void UTargetingComponent::DisableLockOn()
{
	if (IsValid(TargetedActor))
	{
		ITargetingSystemInterface::Execute_ToggleTargetingPoint(GetTargetedActor(), false);
		TargetedActor = nullptr;

		// Switch CameraMode To UnLock
		LocalCameraModeComponent->SetCameraModeOfClass(UnLockCameraMode);		

		LocalCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;		  
		LocalCharacter->bUseControllerRotationYaw = false;
	}
}

void UTargetingComponent::SetLockOnToTarget()
{
	if (IsValid(LocalCameraModeComponent))
	{
		// Switch CameraMode To LockOn
		LocalCameraModeComponent->SetCameraModeOfClass(LockOnCameraMode);
		ITargetingSystemInterface::Execute_ToggleTargetingPoint(GetTargetedActor(), true);

		LocalCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		LocalCharacter->bUseControllerRotationYaw = true;
	}
}

void UTargetingComponent::StaticSwitchToNewTarget(bool RightDirection)
{
	if (TargetedActor)
	{
		TMap<AActor*, float> LocalPotentialTargets;

		for (AActor*& Elem : PotentialTargets)
		{
			if (Elem != TargetedActor)
			{
				float LocalDistance = UKismetMathLibrary::Vector_Distance(GetOwner()->GetActorLocation(), Elem->GetActorLocation());

				FRotator RequiredRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), Elem->GetActorLocation());
				FRotator DeltaRotation;

				ACharacter* LocalOwnerCharacter = Cast<ACharacter>(GetOwner());

				DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(LocalOwnerCharacter->GetControlRotation(), RequiredRotation);

				if (RightDirection == 1)
				{
					if (DeltaRotation.Yaw < 0.f && DeltaRotation.Yaw > -100.f)
					{
						LocalPotentialTargets.Add(Elem, DeltaRotation.Yaw);
					}
					else
					{
						LocalPotentialTargets.Add(Elem, -10000.f);
					}
				}
				else
				{
					if (DeltaRotation.Yaw > 0.f && DeltaRotation.Yaw < 100.f)
					{
						LocalPotentialTargets.Add(Elem, DeltaRotation.Yaw);
					}
					else
					{
						LocalPotentialTargets.Add(Elem, 10000.f);
					}
				}
			}
		}

		if (LocalPotentialTargets.Num() > 0)
		{
			TArray<AActor*> LocalTargets;
			TArray<float> LocalAngles;
			LocalPotentialTargets.GenerateKeyArray(LocalTargets);
			LocalPotentialTargets.GenerateValueArray(LocalAngles);

			if (RightDirection == 1)
			{
				int32 FoundIndex;
				const float MaxValue = FMath::Max<float>(LocalAngles, &FoundIndex);
				if (MaxValue > -10000.f)
				{
					DisableLockOn();
					TargetedActor = LocalTargets[FoundIndex];
					SetLockOnToTarget();
				}

			}
			else
			{
				int32 FoundIndex;
				const float MinValue = FMath::Min<float>(LocalAngles, &FoundIndex);
				if (MinValue < 10000.f)
				{
					DisableLockOn();
					TargetedActor = LocalTargets[FoundIndex];
					SetLockOnToTarget();
				}
			}

		}
	}
}

void UTargetingComponent::UpdatePotentialTargets()
{
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.AddUnique(GetOwner());

	// Returns a array of actors that overlap the given sphere
	UKismetSystemLibrary::SphereOverlapActors(GetOwner(), GetOwner()->GetActorLocation(), TargetingRadius, TargetsType, ClassToTarget, ActorsToIgnore, OverlappedActors);

	TArray<AActor*> ValidOverlappedActors;
	for (AActor*& Elem : OverlappedActors)
	{
		if (CanBeTargeted(Elem))
		{
			ValidOverlappedActors.Add(Elem);
		}
	}
	PotentialTargets = ValidOverlappedActors;
}

bool UTargetingComponent::CanBeTargeted(AActor* ActorToTarget)
{
	bool bCanBeTargeted = false;
	ACharacterBase* Target = Cast<ACharacterBase>(ActorToTarget);
	
	check(IsValid(Target));

	FGameplayTagContainer TagContainer;
	Target->GetOwnedGameplayTags(TagContainer);
	bCanBeTargeted = LocalCombatComponent->GetCombatStatus().HasTag(FGameplayTag::RequestGameplayTag("Status.Combat.InCombat"))
		|| TagContainer.HasTag(FGameplayTag::RequestGameplayTag("Character.AI"))
		|| (!TagContainer.HasTag(FGameplayTag::RequestGameplayTag("State.Death")));
	
	return bCanBeTargeted;
}

float UTargetingComponent::CalculateAngleFromCamera(const AActor* TargetActor)
{
	FRotator FinalRotation;
	if (TargetActor && OwnerCamera)
	{
		FRotator RequiredRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCamera->GetComponentLocation(), TargetActor->GetActorLocation());
		ACharacter* LocalOwnerCharacter = Cast<ACharacter>(GetOwner());
		FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(RequiredRotation, LocalOwnerCharacter->GetControlRotation());
		FinalRotation = DeltaRotation;
	}

	return UKismetMathLibrary::Abs(UKismetMathLibrary::Abs(FinalRotation.Yaw) + UKismetMathLibrary::Abs(FinalRotation.Pitch));
}
