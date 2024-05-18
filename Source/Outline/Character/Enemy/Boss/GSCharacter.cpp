// Fill out your copyright notice in the Description page of Project Settings.


#include "GSCharacter.h"
#include "Outline/Objects/TraceAOE.h"
#include "Outline/Objects/EnemyDefenseProperties.h"
#include "Outline/Weapon/GreatSwordWeapon.h"
#include "Outline/Components/EnemyCombatComponent.h"
#include "Outline/Components/CollisionManagerComponent.h"


AGSCharacter::AGSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGSCharacter::BeginPlay()
{
	Super::BeginPlay();


	Health = 100.f;
	MaxHealth = 100.f;

	/**
	* Start Initialize Controller
	*/
	

	/**
	* Start Initialize Weapon 
	*/
	FTransform SpawnTransform;
	SpawnTransform.SetScale3D(FVector(1.f, 1.f, 1.f));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	SpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;
	SpawnParameters.Owner = this;

	AGreatSwordWeapon* EquippedWeapon = GetWorld()->SpawnActor<AGreatSwordWeapon>(
		WeaponClassToSpawn,
		SpawnTransform,
		SpawnParameters
	);

	// AWeaponBase* EquippedWeapon = NewObject<AGreatSwordWeapon>(this, AGreatSwordWeapon::StaticClass());
	EquippedWeapon->EquipWeapon();
	GetCombatComponent()->SetEquippedWeapon(EquippedWeapon);

	UTraceBase* RightHandTrace;
	TArray<FName> RightHandTraceSockets;
	RightHandTraceSockets.Add(FName("Start"));
	RightHandTraceSockets.Add(FName("End"));
	GetCollisionComponent()->ConstructTraceOfClass(UTraceBase::StaticClass(), RightHandTrace);
	RightHandTrace->TraceGameplayTag = FGameplayTag::RequestGameplayTag(FName("Trace.Right Hand Weapon"));
	RightHandTrace->SetTraceMeshInfo(EquippedWeapon->WeaponMeshComponent, RightHandTraceSockets);

	UTraceBase* AoeTrace;
	TArray<FName> AoeTraceSockets;
	AoeTraceSockets.Add(FName("AoeCenter"));
	GetCollisionComponent()->ConstructTraceOfClass(UTraceAOE::StaticClass(), AoeTrace);
	AoeTrace->TraceGameplayTag = FGameplayTag::RequestGameplayTag(FName("Trace.Aoe.Expanding"));
	AoeTrace->SetTraceMeshInfo(EquippedWeapon->WeaponMeshComponent, AoeTraceSockets);

	UDefenseProperties* ConstructedProperty;
	GetCombatComponent()->ConstructDefensePropertyOfClass(UEnemyDefenseProperties::StaticClass(), ConstructedProperty);
	if (IsValid(ConstructedProperty))
	{
		GetCombatComponent()->SetDefenseProperty(ConstructedProperty);
	}
}