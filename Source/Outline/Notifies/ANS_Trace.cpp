// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Trace.h"
#include "Outline/Objects/TraceBase.h"
#include "Outline/Components/CollisionManagerComponent.h"

void UANS_Trace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(MeshComp->GetOwner()))
	{
		CollisionComp = MeshComp->GetOwner()->GetComponentByClass<UCollisionManagerComponent>();
		if (IsValid(CollisionComp))
		{
			for (FGameplayTag TraceTag : TraceToToggle)
			{
				UTraceBase* FoundTrace;
				CollisionComp->GetTraceOfGameplayTag(TraceTag, FoundTrace);
				if (IsValid(FoundTrace))
				{
					FoundTrace->ConstructAttackPropertyOfObject(AttackProperty);
					FoundTrace->ToggleTrace(true);
				}
			}
		}
	}
}

void UANS_Trace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (IsValid(CollisionComp))
	{
		for (FGameplayTag TraceTag : TraceToToggle)
		{
			UTraceBase* FoundTrace;
			CollisionComp->GetTraceOfGameplayTag(TraceTag, FoundTrace);
			if (IsValid(FoundTrace))
			{
				FoundTrace->ToggleTrace(false);
			}
		}
	}
}
