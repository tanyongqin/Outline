// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceAOE.h"
#include "Outline/Outline.h"
#include "Kismet/KismetSystemLibrary.h"

void UTraceAOE::DoCollisionTrace_Implementation()
{
	checkf(IsValid(TraceOwner), TEXT("%s: Not SetOwner"), *(GetClass()->GetDisplayNameText().ToString()));

	for (FName SocketName : TracePrimitiveComponentSocketNames)
	{
		if (TracePrimitiveComponent->DoesSocketExist(SocketName))
		{

			// TArray<FHitResult>& OutHits, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime

			TArray<FHitResult> OutHits;

			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(TraceOwner);

			bool bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
				GetWorld(),
				TracePrimitiveComponent->GetSocketLocation(SocketName),
				TracePrimitiveComponent->GetSocketLocation(SocketName),
				Radius,
				UEngineTypes::ConvertToTraceType(ECC_SkeletalMesh),
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				OutHits,
				true
			);

			for (FHitResult HitResult : OutHits)
			{
				OnTraceHit(HitResult);
			}
		}
	}
}
