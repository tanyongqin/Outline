// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModeComponent.h"
#include "Outline/Objects/CameraModeBase.h"

UCameraModeComponent::UCameraModeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCameraModeComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCameraModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentCameraMode)
	{
		CurrentCameraMode->TickCameraMode(DeltaTime);
	}
}

void UCameraModeComponent::InitializeCameraModeComponent_Implementation(UCameraComponent* NewCameraComponent, USpringArmComponent* NewSpringArmComponent)
{
	CameraComponent = NewCameraComponent;
	SpringArmComponent = NewSpringArmComponent;
}

void UCameraModeComponent::SetCameraModeOfClass(TSubclassOf<UCameraModeBase> NewCameraModeClass)
{
	if (CurrentCameraMode)
	{
		if (CurrentCameraMode->GetClass() != NewCameraModeClass)
		{
			CurrentCameraMode->EndCameraMode();
			UCameraModeBase* LocalCreatedCameraMode = nullptr;
			ConstructCameraModeOfClass(NewCameraModeClass, LocalCreatedCameraMode);
			CurrentCameraMode = LocalCreatedCameraMode;

			CurrentCameraMode->StartCameraMode();

		}
	}
	else
	{
		UCameraModeBase* LocalCreatedCameraMode = nullptr;
		ConstructCameraModeOfClass(NewCameraModeClass, LocalCreatedCameraMode);
		CurrentCameraMode = LocalCreatedCameraMode;

		CurrentCameraMode->StartCameraMode();
	}
}

void UCameraModeComponent::ConstructCameraModeOfClass(TSubclassOf<UCameraModeBase> NewCameraModeClass, UCameraModeBase*& CreatedCameraMode)
{
	if (NewCameraModeClass)
	{
		UCameraModeBase* LocalNewCameraMode = NewObject<UCameraModeBase>(GetOwner(), NewCameraModeClass);
		CreatedCameraMode = LocalNewCameraMode;

		LocalNewCameraMode->CameraModeComponent = this;
		LocalNewCameraMode->ConstructCameraMode();
		return;
	}
	CreatedCameraMode = nullptr;
}

