#pragma once

#include "CoreMinimal.h"
#include "AbilityMontages.generated.h"

class UAbilityBase;

USTRUCT(BlueprintType)
struct FAbilityMontages
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAbilityBase> Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UAnimMontage*> ListOfMontages;
};