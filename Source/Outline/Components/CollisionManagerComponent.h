// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionManagerComponent.generated.h"

class UTraceBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class OUTLINE_API UCollisionManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionManagerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traces Info")
	TArray<UTraceBase*> ActiveTraceObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traces Info")
	TArray<UTraceBase*> CreatedTraceObjects;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Collision Base Functions")
	void ConstructTraceOfClass(TSubclassOf<UTraceBase> TraceClassToConstruct, UTraceBase*& CreatedTraceObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Collision Base Functions")
	void GetTraceOfGameplayTag(FGameplayTag TraceToFind, UTraceBase*& FoundTrace);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Collision Base Functions")
	void GetTraceByClass(TSubclassOf<UTraceBase> TraceToFind, UTraceBase*& FoundTrace);

	UFUNCTION(BlueprintCallable, Category = "Collision Base Functions")
	void RemoveTraceFromActiveTraces(UTraceBase* TraceToRemove) { ActiveTraceObjects.Remove(TraceToRemove); }

	UFUNCTION(BlueprintCallable, Category = "Collision Base Functions")
	void RemoveTraceFromCreatedTraces(UTraceBase* TraceToRemove) { CreatedTraceObjects.Remove(TraceToRemove); }

	UFUNCTION(BlueprintCallable, Category = "Collision Base Functions")
	void AddTraceToActiveTraces(UTraceBase* TraceToAdd) { ActiveTraceObjects.Add(TraceToAdd); }

	UFUNCTION(BlueprintCallable, Category = "Collision Base Functions")
	void ClearAvailableTraceObjects() { ActiveTraceObjects.Empty(); CreatedTraceObjects.Empty(); }
		
};
