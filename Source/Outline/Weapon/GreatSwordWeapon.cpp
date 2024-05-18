// Fill out your copyright notice in the Description page of Project Settings.

#include "GreatSwordWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Outline/Character/CharacterBase.h"

AGreatSwordWeapon::AGreatSwordWeapon()
{
	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

void AGreatSwordWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AGreatSwordWeapon::EquipWeapon_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Initialize Weapon"));
	FWeaponDetails WeaponDetail;
	WeaponDetail.WeaponMesh = WeaponMeshComponent;
	WeaponDetail.EquippingSocket = FName("weapon_r");
	WeaponDetail.UnEquippingSocket = FName("weapon_r");
	RegisterWeapon(WeaponDetail);

	// TODO Attach The Weapon to Component
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(GetOwner());
	if (IsValid(OwnerCharacter))
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		WeaponMeshComponent->AttachToComponent(
			OwnerCharacter->GetMesh(),
			AttachmentRules,
			FName("weapon_r")
		);
	}
}

void AGreatSwordWeapon::UnEquipWeapon_Implementation()
{
}

