// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "BufferingBase.generated.h"

UENUM(BlueprintType)
enum class EInputBufferType : uint8
{
	NO_BUFFER UMETA(DisplayName = "No Buffer"),
	LAST_REGISTERED UMETA(DisplayName = "Last Registered"),
	INSTANT_FIRE UMETA(DisplayName = "Instant Fire"),
	HIGHEST_PRIORITY UMETA(DisplayName = "Highest Priority"),
};

class UPlayerStateBase;

UCLASS()
class OUTLINE_API UBufferingBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffering Properties")
	TArray<FName> AllowedInputActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffering Properties")
	EInputBufferType BufferingState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffering Properties")
	UPlayerStateBase* EffectedPlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffering Properties")
	FName BufferedInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffering Properties")
	FGameplayTag BufferGameplayTag;

public:
	UFUNCTION(BlueprintCallable)
	void TrySaveAsInputBuffer(FName InputAction);

	UFUNCTION(BlueprintCallable)
	void EndBufferingObject();

	UFUNCTION(BlueprintCallable)
	void SetBaseStateToEffect(UPlayerStateBase* PlayerState) { EffectedPlayerState = PlayerState; }

	UFUNCTION(BlueprintCallable)
	void SetBufferingState(EInputBufferType StateToBuffer) { BufferingState = StateToBuffer; }
};
