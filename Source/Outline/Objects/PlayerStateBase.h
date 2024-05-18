// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "PlayerStateBase.generated.h"

class UBufferingBase;

UCLASS()
class OUTLINE_API UPlayerStateBase : public UStateBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class ACharacterBase* OwnerCharacter;

	UPROPERTY()
	class UAbilityManagerComponent* LocalAbilityManager;
	
	UPROPERTY()
	class UTargetingComponent* LocalTargetingComponent;

	UPROPERTY(EditAnywhere, Category = "Buffer")
	TArray<UBufferingBase*> BufferingObjects;

	UPROPERTY(EditAnywhere, Category = "Buffer")
	UBufferingBase* DefaultBufferObject;

	UPROPERTY(VisibleAnywhere, Category = "Buffer")
	FName BufferedInput;

public:

	/* State Main Events */
	virtual void ConstructState() override;

	virtual void ClearStateValues() override;
	
	/*
	* Getter
	*/
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<UBufferingBase*> GetBufferingObjects() { return BufferingObjects; }

	UFUNCTION(BlueprintCallable, Category = "Getters")
	void ConstructDefaultAllowedInputs(TArray<FName> AllowedInputs);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	void ModifyDefaultAllowedInputs(TArray<FName> AllowedInputs);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE FName GetBufferedInput() const { return BufferedInput; }

	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE ACharacterBase* GetOwnerCharacter() const { return OwnerCharacter; }

	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE UAbilityManagerComponent* GetLocalAbilityManager() const { return LocalAbilityManager; }

	UFUNCTION(BlueprintCallable, Category = "Getters")
	FORCEINLINE UTargetingComponent* GetLocalTargetingComponent() const { return LocalTargetingComponent; }

	/*
	* Setter
	*/
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBufferedInput(FName InputToBuffer) { BufferedInput = InputToBuffer; }

	bool GetCanAllowStateWithInput(FName InputAction);

	void TrySaveAsBufferedInput(FName InputActionToSave);

	UFUNCTION(BlueprintCallable)
	void RotateToTargetedActor(float alpha = 0.1);

	void AddBufferingObject(UBufferingBase* NewBufferObject);

	void RemoveBufferingObject(UBufferingBase* BufferObjectToRemove) { BufferingObjects.Remove(BufferObjectToRemove); }

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Player State Base Functions", meta = (DisplayName = "Fire Buffered Input"))
	void FireBufferedInput();

	UFUNCTION(BlueprintCallable, Category = "Player State Base Functions")
	void RemoveAllNoneBufferingObjects();
};
