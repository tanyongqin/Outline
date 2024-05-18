// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionManagerComponent.h"
#include "Outline/Objects/TraceBase.h"

// Sets default values for this component's properties
UCollisionManagerComponent::UCollisionManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollisionManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UCollisionManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	for (UTraceBase* ActiveTrace : ActiveTraceObjects)
	{
		if (ActiveTrace)
		{
			ActiveTrace->TickTrace(DeltaTime);
		}
	}
}

void UCollisionManagerComponent::ConstructTraceOfClass(TSubclassOf<class UTraceBase> TraceClassToConstruct, UTraceBase*& CreatedTraceObject)
{
	CreatedTraceObject = nullptr;
	if (TraceClassToConstruct)
	{
		UTraceBase* LocalNewTrace;
		LocalNewTrace = NewObject<UTraceBase>(GetOwner(), TraceClassToConstruct);
		CreatedTraceObjects.AddUnique(LocalNewTrace);
		LocalNewTrace->TraceOwner = GetOwner();
		LocalNewTrace->ConstructTrace();
		CreatedTraceObject = LocalNewTrace;
	}
}

void UCollisionManagerComponent::GetTraceOfGameplayTag(FGameplayTag TraceCollisionToFind, UTraceBase*& FoundTraceCollision)
{
	FoundTraceCollision = nullptr;
	if (CreatedTraceObjects.Num() > 0)
	{
		for (int32 i = 0; i < CreatedTraceObjects.Num(); i++)
		{
			if (CreatedTraceObjects[i])
			{
				if (CreatedTraceObjects[i]->TraceGameplayTag == TraceCollisionToFind)
				{
					FoundTraceCollision = CreatedTraceObjects[i];
					return;
				}
			}
		}
	}
}

void UCollisionManagerComponent::GetTraceByClass(TSubclassOf< class UTraceBase> TraceToFind, UTraceBase*& FoundTrace)
{
	FoundTrace = nullptr;
	if (TraceToFind)
	{
		if (CreatedTraceObjects.Num() > 0)
		{
			for (int32 i = 0; i < CreatedTraceObjects.Num(); i++)
			{
				if (CreatedTraceObjects[i])
				{
					if (CreatedTraceObjects[i]->GetClass() == TraceToFind)
					{
						FoundTrace = CreatedTraceObjects[i];
						return;
					}
				}
			}
		}
	}

}


