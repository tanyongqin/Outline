// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CameraModeBase.generated.h"

class UCameraPropertyBase;

UCLASS(Blueprintable, BlueprintType)
class OUTLINE_API UCameraModeBase : public UObject
{
	GENERATED_BODY()
	
public:
	UCameraModeBase();

	UPROPERTY(BlueprintReadWrite, Category = "Initialization")
	FGameplayTag CameraModeStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	TArray<TSubclassOf<UCameraPropertyBase>> CameraProperties;

	UPROPERTY(BlueprintReadOnly, Category = "Base Variables")
	class UCameraModeComponent* CameraModeComponent;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Tick Values")
	float TimePassed;

	UPROPERTY(BlueprintReadWrite, Category = "Initialization")
	TArray<UCameraPropertyBase*> CreatedCameraProperties;


public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void ConstructCameraMode();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void InitializeCameraProperties();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void StartCameraMode();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void TickCameraMode(float TickValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Mode Setters")
	void SetCameraModeStatus(FGameplayTag NewCameraModeStatus);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Camera Mode Setters")
	void OnUpdatedCameraModeStatus();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void EndCameraMode();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Mode Getters")
	void GetCameraPropertyOfType(FGameplayTag PropertyTypeToFind, UCameraPropertyBase*& FoundCameraProperty);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Mode Getters")
	void GetCameraPropertyOfClass(TSubclassOf<UCameraPropertyBase> PropertyClassToFind, UCameraPropertyBase*& FoundCameraProperty);

	UFUNCTION(BlueprintCallable, Category = "Camera Mode Getters")
	void ConstructCameraPropertyOfClass(TSubclassOf<UCameraPropertyBase> NewCameraPropertyClass, UCameraPropertyBase*& CreatedCameraProperty);
};
