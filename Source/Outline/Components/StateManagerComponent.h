// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Outline/Objects/StateBase.h"
#include "StateManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedActiveState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OUTLINE_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateManagerComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Base Dispatchers")
	FOnUpdatedActiveState OnUpdatedActiveState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UStateBase*> ActivatableStates;

	// ״̬����, �Ѽ���?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<TSubclassOf<UStateBase>> QueuedStates;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Base Variables")
	AActor* PerformingActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	UStateBase* CurrentActiveState;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ��ʼ��״̬���������
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization Functions")
	void InitializeStateManagerComponent(AActor* NewPerformingActor);
	// ����ͼδʵ��, Ĭ��ʹ�ô�ʵ��
	virtual void InitializeStateManagerComponent_Implementation(AActor* NewPerformingActor);

	// ����ָ��״̬
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void PerformStateOfClass(TSubclassOf<UStateBase> StateToSet);

	// ���Լ���ָ��״̬
	UFUNCTION(BlueprintCallable, Category = "Setters")
	bool TryPerformStateOfClass(TSubclassOf<UStateBase> StateToSet, bool ConditionCheck = true);

	// �������״̬, �����һ����Ч״̬
	UFUNCTION(BlueprintCallable, Category = "Setters")
	bool TryPerformStatesOfClass(TArray <TSubclassOf<UStateBase>> StatesToSet, bool ConditionCheck = true);

	// ���״̬��������
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void AddToQueuedStates(TSubclassOf<UStateBase> NewQueuedState) { QueuedStates.AddUnique(NewQueuedState); }

	// �Ӷ������Ƴ�״̬
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void RemoveFromQueuedStates(TSubclassOf<UStateBase> QueuedStateToRemove) { QueuedStates.Remove(QueuedStateToRemove); }

	// �������״̬������?
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void TrySetQueuedState(TSubclassOf<UStateBase> StateToQueue, bool ConditionCheck = true);

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCurrentActiveState(UStateBase* NewCurrentActiveState);


	/* Getters */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UStateBase* GetCurrentActiveState() { return CurrentActiveState; }

	// ��ȡָ��״̬
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetStateOfClass(TSubclassOf<UStateBase> StateToSearch, UStateBase*& FoundState);

	// ��ȡָ��״̬������״̬, ��һ�����ҵ���
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetChildStateOfClass(TSubclassOf<UStateBase> StateToSearch, UStateBase*& FoundState);

	// ���Դӿɼ���״̬�б��л�ȡ������, ������, �����Ƿ��ִ��
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	bool GetCanPerformStateOfClass(TSubclassOf<UStateBase> ClassToLookFor);

	// ��ȡ����ָ����ǩ��״̬(��һ��״̬)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UStateBase* GetStateOfGameplayTag(FGameplayTag StateGameplayTag);

	// ��ȡ�ɼ����״̬�б�
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	TArray<UStateBase*> GetActivatableStates() { return ActivatableStates; }

	// ��ȡ��ӵ�״̬
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	TArray<TSubclassOf<UStateBase>> GetQueuedStates() { return QueuedStates; }

	// ���Դӿɼ���״̬�б��л�ȡ������, ������, �����Ƿ�ɼ������
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	bool GetCanSetQueuedStateOfClass(TSubclassOf<UStateBase> StateToSearch);

	// ����������״̬
	/* Construction */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ConstructStateOfClass(TSubclassOf<UStateBase> StateToConstruct, UStateBase*& ConstructedState);

	// ������
	/* Clears All The Arrays Associated For Finding and Setting States*/
	UFUNCTION(BlueprintCallable, Category = "Clearing")
	void ClearStatesComponent() { ActivatableStates.Empty(); QueuedStates.Empty(); CurrentActiveState = nullptr; }
};
