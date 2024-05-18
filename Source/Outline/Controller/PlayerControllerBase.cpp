// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Outline/HUD/GameHUD.h"
#include "Outline/HUD/CharacterOverlay.h"
#include "Outline/Objects/PlayerStateBase.h"
#include "Outline/DataAssets/BaseEnemy_PDA.h"
#include "Outline/Character/Enemy/EnemyCharacterBase.h"
#include "Outline/Character/Player/PlayerCharacterBase.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/TargetingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

APlayerControllerBase::APlayerControllerBase()
{
	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));
}

void APlayerControllerBase::InitializeController()
{
	StateManager->InitializeStateManagerComponent(GetPawn());
	LocalTargetingComponent = GetPawn()->GetComponentByClass<UTargetingComponent>();
}

void APlayerControllerBase::UpdateHUDInfo(AActor* ActorToUpdate)
{
	AGameHUD* HUD = Cast<AGameHUD>(GetHUD());
	if (IsValid(HUD)) 
	{
		if (!IsValid(HUD->CharacterOverlay))
		{
			HUD->AddCharacterOverlay();
		}

		// Set Target Information		
		if (IsValid(ActorToUpdate))
		{
			AEnemyCharacterBase* Target = Cast<AEnemyCharacterBase>(ActorToUpdate);
			FName TargetName = Target->AssociatedDataAsset->EnemyName;

			HUD->CharacterOverlay->TargetName->SetText(FText::FromName(TargetName));

			float TargetPercent = Target->Health / Target->MaxHealth;
			HUD->CharacterOverlay->TargetHealthBar->SetPercent(TargetPercent);

			if (TargetPercent == 0.f)
			{
				UTargetingComponent* TargetingComponent = GetPawn()->GetComponentByClass<UTargetingComponent>();
				TargetingComponent->DisableLockOn();

				HUD->CharacterOverlay->RemoveFromParent();
				HUD->AddGameOver(true);
			}
		}
		
		APlayerCharacterBase* OwnerCharacter = Cast<APlayerCharacterBase>(GetPawn());
		float OwnerPercent = OwnerCharacter->Health / OwnerCharacter->MaxHealth;			

		HUD->CharacterOverlay->HealthBar->SetPercent(OwnerPercent);

		if (OwnerPercent == 0.f)
		{
			HUD->CharacterOverlay->RemoveFromParent();
			HUD->AddGameOver(false);
		}
	}
}

FVector APlayerControllerBase::GetDirectionFromMovementInputs()
{
	return GetPawn()->GetMovementComponent()->GetLastInputVector(); 
}

bool APlayerControllerBase::GetIsControllingCharacter()
{
	APlayerCharacterBase* PlayerCharacter = Cast<APlayerCharacterBase>(GetPawn());

	check(IsValid(PlayerCharacter));

	FGameplayTagContainer TagContainer;
	PlayerCharacter->GetOwnedGameplayTags(TagContainer);
	return TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.Player")));
}


bool APlayerControllerBase::DoesStateAllowInput(FName InputAction)
{
	if (IsValid(StateManager) && IsValid(StateManager->GetCurrentActiveState()))
	{
		UPlayerStateBase* CurrentActiveState = Cast<UPlayerStateBase>(StateManager->GetCurrentActiveState());
		bool bCanAllow = CurrentActiveState->GetCanAllowStateWithInput(InputAction);
		if (!bCanAllow)
		{			
			CurrentActiveState->TrySaveAsBufferedInput(InputAction);
			return false;
		}
	}
	return true;
}

bool APlayerControllerBase::CanFireInput(FName InputAction)
{
	APlayerCharacterBase* PlayerCharacter = Cast<APlayerCharacterBase>(GetPawn());
	return PlayerCharacter->DoesInputExistInMapping(InputAction);
}