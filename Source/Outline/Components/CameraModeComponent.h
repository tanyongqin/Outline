// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraModeComponent.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCameraModeBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTLINE_API UCameraModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCameraModeComponent();

	UPROPERTY(BlueprintReadWrite, Category = "BaseVariables")
	UCameraModeBase* CurrentCameraMode;

	UPROPERTY(BlueprintReadWrite, Category = "BaseVariables")
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, Category = "BaseVariables")
	USpringArmComponent* SpringArmComponent;
protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization Functions")
	void InitializeCameraModeComponent(UCameraComponent* NewCameraComponent, USpringArmComponent* NewSpringArmComponent);
	virtual void InitializeCameraModeComponent_Implementation(UCameraComponent* NewCameraComponent, USpringArmComponent* NewSpringArmComponent);

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void SetCameraModeOfClass(TSubclassOf<UCameraModeBase> NewCameraModeClass);

	UFUNCTION(BlueprintCallable, Category = "Base Functions")
	void ConstructCameraModeOfClass(TSubclassOf<UCameraModeBase> NewCameraModeClass, UCameraModeBase*& CreatedCameraMode);
		
};
