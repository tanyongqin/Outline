// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceBase.h"
#include "Outline/Outline.h"
#include "Outline/Objects/AttackProperties.h"
#include "Outline/Components/CollisionManagerComponent.h"
#include "Outline/Components/CombatComponent.h"
#include "Outline/Character/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTraceBase::ConstructTrace()
{
	HitActorTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Player")));
	HitActorTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.AI")));
}

void UTraceBase::TickTrace(float DeltaSeconds)
{
	// This Only Runs if the Collision Trace is Active. It only Gets Activated When the "ANS_Trace" is Used
	DoCollisionTrace();
}

void UTraceBase::ToggleTrace(bool bToggle)
{
	UCollisionManagerComponent* CollisionManager = TraceOwner->GetComponentByClass<UCollisionManagerComponent>();
	if (IsValid(CollisionManager))
	{
		if (bToggle)
		{
			CollisionManager->AddTraceToActiveTraces(this);
		}
		else
		{
			CollisionManager->RemoveTraceFromActiveTraces(this);
			HitActors.Empty();
		}
	}	
}

void UTraceBase::OnTraceHit(FHitResult HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (HitActor && CanActorBeHit(HitActor))
	{
		HitActors.AddUnique(HitActor);
		if (IsValid(AttackProperty))
		{
			AttackProperty->SetHitResult(HitResult);
			UCombatComponent* CombatComponnet = TraceOwner->GetComponentByClass<UCombatComponent>();
			if (IsValid(CombatComponnet))
			{
				CombatComponnet->SetAttackProperty(AttackProperty);				
			}
			ApplyDamageToHitActor(HitActor);
		}
	}
}

bool UTraceBase::CanActorBeHit(AActor* Actor)
{
	if (HitActors.Contains(Actor))
	{
		return false;
	}

	ACharacterBase* HitActor = Cast<ACharacterBase>(Actor);
	if (IsValid(HitActor))
	{
		FGameplayTagContainer TagContainer;
		HitActor->GetOwnedGameplayTags(TagContainer);
		return TagContainer.HasAny(HitActorTags) || HitActor->ActorHasTag(FName("Breakable"));
	}

	return false;
}

void UTraceBase::ApplyDamageToHitActor(AActor* DamagedActor)
{
	UCombatComponent* CombatComponnet = DamagedActor->GetComponentByClass<UCombatComponent>();
	if (IsValid(CombatComponnet))
	{
		CombatComponnet->SetReceivedAttackProperty(AttackProperty);
		UGameplayStatics::ApplyDamage(DamagedActor, 1.f, nullptr, TraceOwner, nullptr);
	}
	else 
	{
		UGameplayStatics::ApplyDamage(DamagedActor, 1.f, nullptr, TraceOwner, nullptr);
	}
}

void UTraceBase::SetTraceMeshInfo(UPrimitiveComponent* NewPrimitiveComponent, TArray<FName> PrimitiveComponentSocketNames)
{
	TracePrimitiveComponent = NewPrimitiveComponent;
	TracePrimitiveComponentSocketNames = PrimitiveComponentSocketNames;
}

void UTraceBase::ConstructAttackPropertyOfObject(UAttackProperties* AttackPropertyToAssign)
{
	if (AttackPropertyToAssign)
	{
		UAttackProperties* LocalNewAttackProperty = DuplicateObject(AttackPropertyToAssign, TraceOwner);
		AttackProperty = LocalNewAttackProperty;
		AttackProperty->SetAttackPropertyOwner(TraceOwner);
		AttackProperty->ConstructAttackPropertry();
	}
}

//void UTraceBase::DoCollisionTrace_Implementation()
//{
//	if (IsValid(TraceOwner) && IsValid(TracePrimitiveComponent))
//	{
//		for (FName SocketName : TracePrimitiveComponentSocketNames)
//		{
//			if (TracePrimitiveComponent->DoesSocketExist(SocketName))
//			{
//				TArray<AActor*> ActorsToIgnore; 
//				TArray<FHitResult> OutHits;
//
//				UKismetSystemLibrary::SphereTraceMulti(
//					GetWorld(),
//					TracePrimitiveComponent->GetSocketLocation(SocketName),
//					TracePrimitiveComponent->GetSocketLocation(SocketName),
//					70.f,
//					ETraceTypeQuery::TraceTypeQuery1,
//					false,					
//					ActorsToIgnore,
//					EDrawDebugTrace::None,
//					OutHits,
//					true,
//					FLinearColor::Red,
//					FLinearColor::Green,
//					0.1f
//				);
//
//				UCollisionManagerComponent* CollisionManager = TraceOwner->GetComponentByClass<UCollisionManagerComponent>();
//				for (FHitResult HitResult : OutHits)
//				{
//					if (CollisionManager->ActiveTraceObjects.Contains(this))
//					{
//						OnTraceHit(HitResult);
//					}
//				}
//			}
//		}
//	}
//}

void UTraceBase::DoCollisionTrace_Implementation()
{
	if (IsValid(TraceOwner) && IsValid(TracePrimitiveComponent))
	{
		TArray<FHitResult> OutHits;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(TraceOwner);

		UKismetSystemLibrary::SphereTraceMulti(
			GetWorld(),
			TracePrimitiveComponent->GetSocketLocation(TracePrimitiveComponentSocketNames[0]),
			TracePrimitiveComponent->GetSocketLocation(TracePrimitiveComponentSocketNames[1]),
			33.f,
			UEngineTypes::ConvertToTraceType(ECC_SkeletalMesh),
			false,
			ActorsToIgnore,
			EDrawDebugTrace::None,
			OutHits,
			true
		);

		UCollisionManagerComponent* CollisionManager = TraceOwner->GetComponentByClass<UCollisionManagerComponent>();
		for (FHitResult HitResult : OutHits)
		{
			if (CollisionManager->ActiveTraceObjects.Contains(this))
			{
				OnTraceHit(HitResult);
			}
		}
	}
}
