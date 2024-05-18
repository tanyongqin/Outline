// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/CombatComponent.h"
#include "Outline/Objects/DefenseProperties.h"
#include "Outline/Objects/StateBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::ReceiveDamage);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("%s, Receive Damage: %f"), *GetName(), Damage);
	UStateManagerComponent* StateManager = GetController()->GetComponentByClass<UStateManagerComponent>();
	if (IsValid(StateManager) && IsValid(StateManager->GetCurrentActiveState()))
	{
		FGameplayTag DeathTag = FGameplayTag::RequestGameplayTag(FName(TEXT("State.Death")), true);
		if (StateManager->GetCurrentActiveState()->StateGameplayTag != DeathTag)
		{
			OnAttackReceived();		
			StateManager->TryPerformStateOfClass(StateManager->GetStateOfGameplayTag(DeathTag)->GetClass(), true);
		}
	}
}

void ACharacterBase::OnAttackReceived()
{
	LocalCombatComponent = GetComponentByClass<UCombatComponent>();
	if (IsValid(LocalCombatComponent) && LocalCombatComponent->OwnerDefenseProperty)
	{
		LocalCombatComponent->OwnerDefenseProperty->ProcessReceivedAttack();
	}
}


