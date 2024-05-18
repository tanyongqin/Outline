// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CameraPropertyBase.generated.h"


UCLASS()
class OUTLINE_API UCameraPropertyBase : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	FGameplayTag PropertyType;

	UPROPERTY(BlueprintReadWrite, Category = "Initialization")
	class UCameraModeBase* CameraMode;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Tick Values")
	float TimePassed;

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void ConstructCameraProperty();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void StartCameraProperty();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Base Functions")
	void TickCameraProperty(float TickValue);
};
