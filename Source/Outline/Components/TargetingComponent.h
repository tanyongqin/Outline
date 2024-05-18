// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCameraModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class OUTLINE_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting Properties")
	AActor* TargetedActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Targeting Properties")
	TArray<AActor*> PotentialTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting Properties")
	float TargetingRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting Properties")
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetsType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting Properties")
	UClass* ClassToTarget = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting Base Values")
	UCameraComponent* OwnerCamera;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting Base Values")
	USpringArmComponent* OwnerSpringArm;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraModeBase> LockOnCameraMode;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraModeBase> UnLockCameraMode;

protected:
	virtual void BeginPlay() override;

private:
	class ACharacterBase* LocalCharacter;
	class UCameraModeComponent* LocalCameraModeComponent;
	class UCombatComponent* LocalCombatComponent;
public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting Component Functions")
	void InitializeTargetingComponent(UCameraComponent* CameraComponent, USpringArmComponent* SpringArmComponent);
	virtual void InitializeTargetingComponent_Implementation(UCameraComponent* CameraComponent, USpringArmComponent* SpringArmComponent);

	UFUNCTION(BlueprintCallable, Category = "Targeting Component Functions")
	void SearchForActorToTarget();

	UFUNCTION()
	void InternalSearchForActorToTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting Component Functions")
	void DisableLockOn();

	UFUNCTION(BlueprintCallable, Category = "Targeting Component Functions")
	void SetLockOnToTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting Component Functions")
	void StaticSwitchToNewTarget(bool RightDirection);

	UFUNCTION(BlueprintCallable, Category = "Targeting Component Functions")
	void UpdatePotentialTargets();

	/* Getters */
	UFUNCTION(BlueprintCallable, Category = "Targeting Component Getters")
	bool CanBeTargeted(AActor* ActorToTarget);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Targeting Component Getters")
	FORCEINLINE AActor* GetTargetedActor() { return TargetedActor; }

	/*    Math Functions     */
	UFUNCTION(BlueprintCallable, Category = "Math Calculations")
	float CalculateAngleFromCamera(const AActor* TargetActor);
		
};
