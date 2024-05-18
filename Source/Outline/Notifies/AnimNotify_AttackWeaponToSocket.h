// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttackWeaponToSocket.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINE_API UAnimNotify_AttackWeaponToSocket : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere)
	bool bIsEquip;

	UPROPERTY(EditAnyWhere)
	int32 SocketIndex;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
