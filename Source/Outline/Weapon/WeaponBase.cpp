// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "GameFramework/Character.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::AttachWeaponAtIndex(int32 Index, bool EquipSlot)
{
	
	ACharacter* Target = Cast<ACharacter>(GetOwner());
	if (Target && WeaponProperties.Num() > 0)
	{		
		FWeaponDetails WeaponDetail = WeaponProperties[Index];
		if (IsValid(WeaponDetail.WeaponMesh))
		{
			FName TargetSocket = EquipSlot ? WeaponDetail.EquippingSocket : WeaponDetail.UnEquippingSocket;
			FAttachmentTransformRules AttachmentRules(
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget,
				true
			);		
			WeaponDetail.WeaponMesh->AttachToComponent(Target->GetMesh(), AttachmentRules, TargetSocket);
		}		
	}
}

void AWeaponBase::RegisterWeapon(FWeaponDetails NewWeapon)
{
	WeaponProperties.Add(NewWeapon);
}

void AWeaponBase::EquipWeapon_Implementation()
{

}

void AWeaponBase::UnEquipWeapon_Implementation()
{

}

void AWeaponBase::AttachAllWeapon(bool EquipSlot)
{
	ACharacter* Target = Cast<ACharacter>(GetOwner());
	if (Target)
	{
		for (struct FWeaponDetails& WeaponDetail : WeaponProperties)
		{
			if (IsValid(WeaponDetail.WeaponMesh))
			{
				FName TargetSocket = EquipSlot ? WeaponDetail.EquippingSocket : WeaponDetail.UnEquippingSocket;
				FAttachmentTransformRules AttachmentRules(
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::SnapToTarget,
					true
				);
				WeaponDetail.WeaponMesh->AttachToComponent(Target->GetMesh(), AttachmentRules, TargetSocket);
			}			
		}		
	}
}



