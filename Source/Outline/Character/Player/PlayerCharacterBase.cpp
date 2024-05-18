// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Outline/Objects/DefenseProperties.h"
#include "Outline/Weapon/PlayerWeaponBase.h"
#include "Outline/DataAssets/BasePlayer_PDA.h"
#include "Outline/Controller/PlayerControllerBase.h"
#include "Outline/Components/StateManagerComponent.h"
#include "Outline/Components/AbilityManagerComponent.h"
#include "Outline/Components/AttributesComponent.h"
#include "Outline/Components/PlayerCombatComponent.h"
#include "Outline/Components/TargetingComponent.h"
#include "Outline/Components/CameraModeComponent.h"
#include "Outline/Components/CollisionManagerComponent.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.4f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AbilityManager = CreateDefaultSubobject<UAbilityManagerComponent>(TEXT("AbilityManager"));
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComp"));
	CombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("CombatComp"));
	
	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComp"));
	CameraModeComponent = CreateDefaultSubobject<UCameraModeComponent>(TEXT("CameraModeComp"));	
	CollisionManager = CreateDefaultSubobject<UCollisionManagerComponent>(TEXT("CollisionManager"));
}

void APlayerCharacterBase::Tick(float DeltaTime)
{
	UStateManagerComponent* StateComp = GetController()->GetComponentByClass<UStateManagerComponent>();

	if (IsValid(StateComp) && IsValid(StateComp->GetCurrentActiveState()))
	{
		GEngine->AddOnScreenDebugMessage(
			0,
			DeltaTime,
			FColor::Green,
			FString::Printf(TEXT("Current Active State: %s"), *StateComp->GetCurrentActiveState()->GetName())
		);
	} 
	else
	{
		GEngine->AddOnScreenDebugMessage(
			0,
			DeltaTime,
			FColor::Green,
			FString::Printf(TEXT("Current Active State: NULL"))
		);
	}
	
	if (IsValid(AbilityManager->GetCurrentActiveAbility()))
	{
		GEngine->AddOnScreenDebugMessage(
			1,
			DeltaTime,
			FColor::Green,
			FString::Printf(TEXT("Current Active Ability: %s"), *AbilityManager->GetCurrentActiveAbility()->GetName())
		);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			1,
			DeltaTime,
			FColor::Green ,
			FString::Printf(TEXT("Current Active Ability: NULL"))		
		);
	}
}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//TODO Need to modify
	Health = 50.f;
	MaxHealth = 50.f;

	APlayerControllerBase* OwnerController = Cast<APlayerControllerBase>(GetController());
	if (IsValid(OwnerController))
	{
		OwnerController->InitializeController();		
	}
	
	if (IsValid(WeaponClassToSpawn))
	{
		FTransform SpawnTransform;
		SpawnTransform.SetScale3D(FVector(1.f, 1.f, 1.f));

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
		SpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;
		SpawnParameters.Owner = this;

		GetWorld()->SpawnActor<AWeaponBase>(
			WeaponClassToSpawn,
			SpawnTransform,
			SpawnParameters
		);
	}
	else 
	{
		// TODO Initialize the default weapon  
	}

	if (IsValid(TargetingComponent))
	{
		TargetingComponent->InitializeTargetingComponent(FollowCamera, CameraBoom);
		TargetingComponent->ClassToTarget = ACharacterBase::StaticClass();
	}

	if (IsValid(CameraModeComponent))
	{
		CameraModeComponent->InitializeCameraModeComponent(FollowCamera, CameraBoom);
	}

	if (IsValid(CombatComponent))
	{
		UDefenseProperties* ConstructedProperty;
		CombatComponent->ConstructDefensePropertyOfClass(UDefenseProperties::StaticClass(), ConstructedProperty);
		if (IsValid(ConstructedProperty))
		{
			CombatComponent->SetDefenseProperty(ConstructedProperty);
		}
	}
}

void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacterBase::UpdateHUDInfo(AActor* ActorToUpdate)
{
	APlayerControllerBase* OwnerController = Cast<APlayerControllerBase>(GetController());
	if (IsValid(OwnerController))
	{
		OwnerController->UpdateHUDInfo(ActorToUpdate);
	}
}

bool APlayerCharacterBase::DoesInputExistInMapping(FName InputToCheck)
{
	AWeaponBase* EquippedWeapon = CombatComponent->GetEquippedWeapon();
	if (EquippedWeapon != nullptr)
	{
		APlayerWeaponBase* PlayerWeapon = Cast<APlayerWeaponBase>(EquippedWeapon);
		TArray<FName> PlayerInputs = PlayerWeapon->AssociatedDataAsset->PlayerInputs;
		
		for (FName Input : PlayerInputs)
		{
			if (Input == InputToCheck)
			{
				return true;
			}
		}
	}
	return false;
}

