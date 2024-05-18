// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterBase.h"
#include "Outline/DataAssets/BaseEnemy_PDA.h"
#include "Outline/Components/AbilityManagerComponent.h"
#include "Outline/Components/AttributesComponent.h"
#include "Outline/Components/EnemyCombatComponent.h"
#include "Outline/Components/CollisionManagerComponent.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Controller/EnemyControllerBase.h"
#include "Outline/Objects/EnemyStateBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetComponent.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	AbilityManager = CreateDefaultSubobject<UAbilityManagerComponent>(TEXT("AbilityManager"));
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComp"));
	CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("CombatComp"));
	CollisionManager = CreateDefaultSubobject<UCollisionManagerComponent>(TEXT("CollisionManager"));
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(IsValid(AssociatedDataAsset), TEXT("Enemy %s: DataAsset is NOT Assigned"), *(GetClass()->GetName()));

	if (!IsValid(AIControllerClass))
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = GetInstigator();
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.OverrideLevel = GetLevel();
		SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save AI controllers into a map
		AController* NewController = GetWorld()->SpawnActor<AController>(AssociatedDataAsset->EnemyController, GetActorLocation(), GetActorRotation(), SpawnInfo);
		if (NewController != nullptr)
		{
			// if successful will result in setting this->Controller 
			// as part of possession mechanics
			NewController->Possess(this);
		}
	}

	MyController = Cast<AEnemyControllerBase>(GetController());
	MyController->InitializeAIController();

	UStateManagerComponent* LocalStateComponent = GetController()->GetComponentByClass<UStateManagerComponent>();
	if (IsValid(LocalStateComponent) && IsValid(AbilityManager) && IsValid(AttributesComponent))
	{
		for (TSubclassOf<UEnemyStateBase> StateToConstruct : AssociatedDataAsset->AvailableEnemyStates)
		{
			UStateBase* ConstructedState = nullptr;
			LocalStateComponent->ConstructStateOfClass(StateToConstruct, ConstructedState);
		}
		AttributesComponent->AssignAttributes(AssociatedDataAsset->AttributesToCreate);
	}
}
