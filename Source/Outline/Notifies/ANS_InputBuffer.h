// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Outline/Objects/BufferingBase.h"
#include "ANS_InputBuffer.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UANS_InputBuffer : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buffer Parameters")
	TArray<FName> AllowedInputs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buffer Parameters")
	EInputBufferType NotifyInputBufferType = EInputBufferType::HIGHEST_PRIORITY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buffer Parameters")
	FGameplayTag StateToModify;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buffer Parameters")
	TSubclassOf<UBufferingBase> BufferingClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buffer Parameters")
	FGameplayTag BufferGameplayTag;

private:
	UPROPERTY()
	UBufferingBase* BufferingObject = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category = "Buffer Setters")
	void SetBufferingObject(UBufferingBase* NewBufferingObject) { BufferingObject = NewBufferingObject; };

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Buffer Getters")
	UBufferingBase* GetBufferingObject() { return BufferingObject; }

public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
