// Fill out your copyright notice in the Description page of Project Settings.

#include "SamuraiCharacter.h"

ASamuraiCharacter::ASamuraiCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ’∂…± Seletal Mesh ‘⁄¥À…Ë÷√
}

void ASamuraiCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASamuraiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// check(PlayerInputComponent);
}
