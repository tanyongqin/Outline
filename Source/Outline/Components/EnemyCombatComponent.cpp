// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCombatComponent.h"
#include "Outline/Character/Enemy/EnemyCharacterBase.h"
#include "Outline/Controller/EnemyControllerBase.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/DataAssets/BaseEnemy_PDA.h"
#include "Outline/Objects/EnemyStateBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

AActor* UEnemyCombatComponent::GetCombatTarget()
{
    if (CombatTargets.Num() > 0)
    {
        return CombatTargets[0];
    }
    return nullptr;
}

void UEnemyCombatComponent::ClearCombatTargets()
{
    CombatTargets.Empty();
}

void UEnemyCombatComponent::AddCombatTarget(AActor* TargetToAdd)
{
    CombatTargets.AddUnique(TargetToAdd);
}

void UEnemyCombatComponent::SetCombatTarget(AActor* NewCombatTarget)
{
    if (CombatTargets.Contains(NewCombatTarget))
    {
        CombatTargets.Swap(0, CombatTargets.Find(NewCombatTarget));
    }
}

void UEnemyCombatComponent::EnterCombat()
{
    AEnemyCharacterBase* OwnerCharacter = Cast<AEnemyCharacterBase>(GetOwner());
    AEnemyControllerBase* OwnerController = Cast<AEnemyControllerBase>(OwnerCharacter->GetController());
    UBlackboardComponent* BlackBoard = OwnerController->GetBlackboardComponent();

    BlackBoard->SetValueAsObject(FName("CombatTarget"), GetCombatTarget());
    UStateManagerComponent* StateComponent = OwnerController->GetComponentByClass<UStateManagerComponent>();
    StateComponent->TryPerformStateOfClass(OwnerCharacter->AssociatedDataAsset->OnSeenState, true);
    
    ACharacterBase* CombatTarget = Cast<ACharacterBase>(GetCombatTarget());
    CombatTarget->UpdateHUDInfo(GetOwner());
}

void UEnemyCombatComponent::ExitCombat()
{
    AEnemyCharacterBase* OwnerCharacter = Cast<AEnemyCharacterBase>(GetOwner());
    AEnemyControllerBase* OwnerController = Cast<AEnemyControllerBase>(OwnerCharacter->GetController());
    UBlackboardComponent* BlackBoard = OwnerController->GetBlackboardComponent();

    ClearCombatTargets();
    BlackBoard->SetValueAsObject(FName("CombatTarget"), nullptr);
}

void UEnemyCombatComponent::RotateEnemyToCombatTarget(float RotateSpeed)
{
    if (IsValid(GetCombatTarget()))
    {
        FVector Direction = GetCombatTarget()->GetActorLocation() - GetOwner()->GetActorLocation();
        FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
        FRotator YawRotation = FMath::Lerp(GetOwner()->GetActorRotation(), TargetRotation, RotateSpeed);

        FRotator NewRotation;
        NewRotation.Roll = GetOwner()->GetActorRotation().Roll;
        NewRotation.Pitch = GetOwner()->GetActorRotation().Pitch;
        NewRotation.Yaw = YawRotation.Yaw;

        GetOwner()->SetActorRotation(NewRotation, ETeleportType::TeleportPhysics);
    }
}
