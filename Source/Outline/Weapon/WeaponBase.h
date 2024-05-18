// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "WeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FWeaponDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Details")
	class UPrimitiveComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Details")
	FName EquippingSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Details")
	FName UnEquippingSocket;
};

UCLASS()
class OUTLINE_API AWeaponBase : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialization")
	FGameplayTagContainer ActorGameplayTags;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = ActorGameplayTags; return; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Base Properties")
	TArray<FWeaponDetails> WeaponProperties;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Weapon Base Functions")
	virtual void AttachWeaponAtIndex(int32 Index, bool EquipSlot);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon Base Functions")
	virtual void RegisterWeapon(FWeaponDetails NewWeapon);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Base Functions")
	void EquipWeapon();
	virtual void EquipWeapon_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Base Functions")
	void UnEquipWeapon();
	virtual void UnEquipWeapon_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Weapon Base Functions")
	virtual void AttachAllWeapon(bool EquipSlot);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	TArray<FWeaponDetails> GetWeaponProperties() { return WeaponProperties; }
};
