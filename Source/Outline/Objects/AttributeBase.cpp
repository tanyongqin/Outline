// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeBase.h"
#include "Kismet/KismetMathLibrary.h"

void UAttributeBase::ModifyAttribute(float ModifyBy)
{
	
	float NewAttributeValue = UKismetMathLibrary::Clamp(
		AttributeValues.AttributeValue + ModifyBy,
		AttributeValues.MinAttributeValue,
		AttributeValues.MaxAttributeValue
	);
	AttributeValues.AttributeValue = NewAttributeValue;
	
	OnValueUpdated.Broadcast(AttributeGameplayTag);
}
