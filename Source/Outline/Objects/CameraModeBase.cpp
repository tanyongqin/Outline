// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModeBase.h"
#include "Outline/Objects/CameraPropertyBase.h"
#include "Outline/Components/CameraModeComponent.h"

UCameraModeBase::UCameraModeBase()
{
}

void UCameraModeBase::SetCameraModeStatus(FGameplayTag NewCameraModeStatus)
{
	CameraModeStatus = NewCameraModeStatus;
	OnUpdatedCameraModeStatus();
}

void UCameraModeBase::GetCameraPropertyOfType(FGameplayTag PropertyTypeToFind, UCameraPropertyBase*& FoundCameraProperty)
{
	FoundCameraProperty = nullptr;
	if (CreatedCameraProperties.Num() > 0)
	{
		for (int32 i = 0; i < CreatedCameraProperties.Num(); i++)
		{
			if (CreatedCameraProperties[i] && CreatedCameraProperties[i]->PropertyType == PropertyTypeToFind)
			{
				FoundCameraProperty = CreatedCameraProperties[i];
				return;
			}
		}
	}
}

void UCameraModeBase::GetCameraPropertyOfClass(TSubclassOf<UCameraPropertyBase> PropertyClassToFind, UCameraPropertyBase*& FoundCameraProperty)
{
	FoundCameraProperty = nullptr;
	if (CreatedCameraProperties.Num() > 0)
	{
		for (int32 i = 0; i < CreatedCameraProperties.Num(); i++)
		{
			if (CreatedCameraProperties[i] && CreatedCameraProperties[i]->GetClass() == PropertyClassToFind)
			{
				FoundCameraProperty = CreatedCameraProperties[i];
				return;
			}
		}
	}
}

void UCameraModeBase::ConstructCameraPropertyOfClass(TSubclassOf<UCameraPropertyBase> NewCameraPropertyClass, UCameraPropertyBase*& CreatedCameraProperty)
{
	if (IsValid(NewCameraPropertyClass) && IsValid(CameraModeComponent))
	{
		UCameraPropertyBase* LocalNewCameraProperty;
		LocalNewCameraProperty = NewObject<UCameraPropertyBase>(CameraModeComponent->GetOwner(), NewCameraPropertyClass);
		CreatedCameraProperty = LocalNewCameraProperty;

		LocalNewCameraProperty->CameraMode = this;
		LocalNewCameraProperty->ConstructCameraProperty();
		CreatedCameraProperties.AddUnique(LocalNewCameraProperty);
		return;
	}
	CreatedCameraProperty = nullptr;
}
