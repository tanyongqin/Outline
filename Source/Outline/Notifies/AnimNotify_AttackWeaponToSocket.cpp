// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackWeaponToSocket.h"
#include "Outline/Components/CombatComponent.h"
#include "Outline/Weapon/WeaponBase.h"
#include "Outline/Character/CharacterBase.h"

void UAnimNotify_AttackWeaponToSocket::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (!IsValid(OwnerCharacter)) return;

	UCombatComponent* Combat = OwnerCharacter->GetComponentByClass<UCombatComponent>();
	if (IsValid(Combat) && IsValid(Combat->GetEquippedWeapon()))
	{
		TArray<FWeaponDetails> WeaponProperties = Combat->GetEquippedWeapon()->GetWeaponProperties();
		if (SocketIndex < WeaponProperties.Num())
		{
			FAttachmentTransformRules AttachmentRules(
				EAttachmentRule::SnapToTarget,
				true
			);

			FWeaponDetails Detail = WeaponProperties[SocketIndex];
			FName TargetSocket = bIsEquip ? Detail.EquippingSocket : Detail.UnEquippingSocket;

			Detail.WeaponMesh->AttachToComponent(
				OwnerCharacter->GetMesh(),
				AttachmentRules,
				TargetSocket
			);
		}
	}
}
