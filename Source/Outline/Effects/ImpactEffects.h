// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ImpactEffects.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FImpactSFX
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> Sound;
};

USTRUCT(BlueprintType)
struct FImpactVFX
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> Emitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator EmitterRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EmitterScale;
};

USTRUCT(BlueprintType)
struct FEffects
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	TEnumAsByte<EPhysicalSurface> SurfaceType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FImpactSFX> ImpactSFXs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FImpactVFX> ImpactVFXs;
};

UCLASS(BlueprintType, Blueprintable)
class OUTLINE_API UImpactEffects : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FEffects> Effects;

private:
	FHitResult HitResult;

public:
	UFUNCTION(BlueprintCallable, Category = "Apply Function")
	void ApplyEffect();

	void ApplyVFX(FImpactVFX VFXToApply);

	void ApplySFX(FImpactSFX SFXToApply);

public:
	/*
	* Setters Function 
	*/
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetEffect(TArray<FEffects> NewEffects) { Effects = NewEffects; };

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetHitResult(FHitResult NewHitResult) { HitResult = NewHitResult; };

	/*
	* Getters Function 
	*/
	UFUNCTION(BlueprintCallable, Category = "Getters")
	FHitResult GetHitResult() { return HitResult; }

};
