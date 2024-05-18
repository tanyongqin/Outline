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

	// 状态队列, 已激活?
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

	// 初始化状态管理器组件
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization Functions")
	void InitializeStateManagerComponent(AActor* NewPerformingActor);
	// 若蓝图未实现, 默认使用此实现
	virtual void InitializeStateManagerComponent_Implementation(AActor* NewPerformingActor);

	// 激活指定状态
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void PerformStateOfClass(TSubclassOf<UStateBase> StateToSet);

	// 尝试激活指定状态
	UFUNCTION(BlueprintCallable, Category = "Setters")
	bool TryPerformStateOfClass(TSubclassOf<UStateBase> StateToSet, bool ConditionCheck = true);

	// 给定多个状态, 激活第一个有效状态
	UFUNCTION(BlueprintCallable, Category = "Setters")
	bool TryPerformStatesOfClass(TArray <TSubclassOf<UStateBase>> StatesToSet, bool ConditionCheck = true);

	// 添加状态到队列中
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void AddToQueuedStates(TSubclassOf<UStateBase> NewQueuedState) { QueuedStates.AddUnique(NewQueuedState); }

	// 从队列中移除状态
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void RemoveFromQueuedStates(TSubclassOf<UStateBase> QueuedStateToRemove) { QueuedStates.Remove(QueuedStateToRemove); }

	// 尝试添加状态到队列?
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void TrySetQueuedState(TSubclassOf<UStateBase> StateToQueue, bool ConditionCheck = true);

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCurrentActiveState(UStateBase* NewCurrentActiveState);


	/* Getters */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UStateBase* GetCurrentActiveState() { return CurrentActiveState; }

	// 获取指定状态
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetStateOfClass(TSubclassOf<UStateBase> StateToSearch, UStateBase*& FoundState);

	// 获取指定状态的子类状态, 第一个查找到的
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetChildStateOfClass(TSubclassOf<UStateBase> StateToSearch, UStateBase*& FoundState);

	// 尝试从可激活状态列表中获取给定类, 若存在, 返回是否可执行
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	bool GetCanPerformStateOfClass(TSubclassOf<UStateBase> ClassToLookFor);

	// 获取带有指定标签的状态(第一个状态)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	UStateBase* GetStateOfGameplayTag(FGameplayTag StateGameplayTag);

	// 获取可激活的状态列表
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	TArray<UStateBase*> GetActivatableStates() { return ActivatableStates; }

	// 获取入队的状态
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	TArray<TSubclassOf<UStateBase>> GetQueuedStates() { return QueuedStates; }

	// 尝试从可激活状态列表中获取给定类, 若存在, 返回是否可加入队列
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	bool GetCanSetQueuedStateOfClass(TSubclassOf<UStateBase> StateToSearch);

	// 构建给定的状态
	/* Construction */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ConstructStateOfClass(TSubclassOf<UStateBase> StateToConstruct, UStateBase*& ConstructedState);

	// 清除组件
	/* Clears All The Arrays Associated For Finding and Setting States*/
	UFUNCTION(BlueprintCallable, Category = "Clearing")
	void ClearStatesComponent() { ActivatableStates.Empty(); QueuedStates.Empty(); CurrentActiveState = nullptr; }
};
