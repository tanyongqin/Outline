// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EMoveset : uint8
{
	EM_COMMON UMETA(DisplayName = "Common"),
	EM_IN_COMBAT UMETA(DisplayName = "In Combat"),
	EM_STRAFING UMETA(DisplayName = "Strafing"),
	EM_STRAFING_WITH_BLOCK UMETA(DisplayName = "Strafing With Block"),
	EM_BLOCKING UMETA(DisplayName = "Blocking"),

	EM_MAX UMETA(DisplayName = "DefaultMAX")
};