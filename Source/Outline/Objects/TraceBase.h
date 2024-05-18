// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "TraceBase.generated.h"

class UAttackProperties;

UCLASS(Blueprintable, BlueprintType, AutoExpandCategories = ("Initialization | Trace Info", "Initialization | Mesh Info", "Initialization | Collision Trace"))
class OUTLINE_API UTraceBase : public UObject
{
	GENERATED_BODY()
	
public:
	/* Trace Information */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization | Trace Info")
	FGameplayTag TraceGameplayTag;

	/* Trace Mesh Information */
	UPROPERTY(BlueprintReadWrite, Category = "Initialization | Mesh Info")
	class UPrimitiveComponent* TracePrimitiveComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Initialization | Mesh Info")
	TArray<FName> TracePrimitiveComponentSocketNames;

	UPROPERTY(BlueprintReadOnly, Category = "Trace Properties")
	AActor* TraceOwner = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Trace Properties | Attack")
	UAttackProperties* AttackProperty;

	/*
	* Hit Information
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Info")
	FGameplayTagContainer HitActorTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Info")
	TArray<AActor*> HitActors;

public:

	UFUNCTION(BlueprintCallable, Category = "Trace Base Functions")
	void ConstructTrace();

	UFUNCTION(BlueprintCallable, Category = "Trace Base Functions")
	void TickTrace(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Trace Base Functions")
	void ToggleTrace(bool bToggle);

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void OnTraceHit(FHitResult HitResult);

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	bool CanActorBeHit(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void ApplyDamageToHitActor(AActor* DamagedActor);

	/* Setters */
	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetTraceMeshInfo(UPrimitiveComponent* NewPrimitiveComponent, TArray<FName> PrimitiveComponentSocketNames);

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void ConstructAttackPropertyOfObject(UAttackProperties* AttackPropertyToAssign);

	/* This function is the function that fires the sphere trace */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Base Functions")
	void DoCollisionTrace();
	virtual void DoCollisionTrace_Implementation();

};
