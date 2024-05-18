// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Outline/Interfaces/GeneralInterface.h"
#include "Outline/Interfaces/PlayerInputs.h"
#include "PlayerControllerBase.generated.h"

class UStateManagerComponent;
class UTargetingComponent;

UCLASS()
class OUTLINE_API APlayerControllerBase : public APlayerController, public IGeneralInterface, public IPlayerInputs
{
	GENERATED_BODY()
	
public:
	APlayerControllerBase();

private:
	UPROPERTY()
	FName LastFiredInput;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateManagerComponent> StateManager;

	UTargetingComponent* LocalTargetingComponent;
public:
	virtual void InitializeController() override;

	virtual void UpdateHUDInfo(AActor* ActorToUpdate) override;

	virtual void SetLastFireInput(FName NewLastFiredInput) override { LastFiredInput = NewLastFiredInput; }

	virtual FName GetLastFireInput() override { return LastFiredInput; }

	virtual FVector GetDirectionFromMovementInputs() override;

	UFUNCTION(BlueprintCallable)
	bool GetIsControllingCharacter();

	UFUNCTION(BlueprintCallable, Category = "Input")
	bool DoesStateAllowInput(FName InputAction);

	UFUNCTION(BlueprintCallable, Category = "Input")
	bool CanFireInput(FName InputAction);
};
