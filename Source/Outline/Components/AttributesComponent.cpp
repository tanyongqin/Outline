// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesComponent.h"
#include "Outline/Objects/AttributeBase.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (int32 i = 0; i < CreatedAttributes.Num(); i++)
	{
		if (CreatedAttributes[i])
		{
			CreatedAttributes[i]->TickAttribute(DeltaTime);
		}

	}
}

void UAttributesComponent::InitializeAttributesComponent_Implementation(const TArray<TSubclassOf<UAttributeBase>>& NewAttributesToCreate)
{
	for (int32 i = 0; i < NewAttributesToCreate.Num(); i++)
	{

		if (NewAttributesToCreate[i])
		{
			UAttributeBase* LocalCreatedAttribute = nullptr;
			ConstructAttributeOfClass(NewAttributesToCreate[i], LocalCreatedAttribute);

		}

	}

}

void UAttributesComponent::AssignAttributes(TArray<UAttributeBase*> AttributesToAssign)
{
	for (int32 i = 0; i < AttributesToAssign.Num(); i++)
	{
		if (AttributesToAssign[i])
		{

			UAttributeBase* LocalNewAttribute = DuplicateObject(AttributesToAssign[i], GetOwner());

			LocalNewAttribute->SetOwningActor(GetOwner());
			LocalNewAttribute->ConstructAttribute();

			CreatedAttributes.AddUnique(LocalNewAttribute);
		}
	}
}

void UAttributesComponent::ClearAttributes()
{
	CreatedAttributes.Empty();
}

void UAttributesComponent::ConstructAttributeOfClass(TSubclassOf<UAttributeBase> AttributeToConstruct, UAttributeBase*& ConstructedAttribute)
{
	ConstructedAttribute = nullptr;
	if (AttributeToConstruct)
	{
		UAttributeBase* LocalNewAttribute;
		LocalNewAttribute = NewObject<UAttributeBase>(GetOwner(), AttributeToConstruct);

		CreatedAttributes.AddUnique(LocalNewAttribute);

		LocalNewAttribute->SetOwningActor(GetOwner());
		LocalNewAttribute->ConstructAttribute();
		ConstructedAttribute = LocalNewAttribute;
	}

}

void UAttributesComponent::GetAttributeOfClass(TSubclassOf<UAttributeBase> AttributeToSearch, UAttributeBase*& FoundAttribute)
{
	FoundAttribute = nullptr;
	for (int32 i = 0; i < CreatedAttributes.Num(); i++)
	{

		if (CreatedAttributes[i])
		{
			if (CreatedAttributes[i]->GetClass() == AttributeToSearch)
			{
				FoundAttribute = CreatedAttributes[i];

				return;
			}
		}

	}

	FoundAttribute = nullptr;
	return;
}

void UAttributesComponent::GetActiveAttributeModifierOfClass(TSubclassOf<UAttributeModifier> AttributeModifierToSearch, UAttributeModifier*& FoundAttributeModifier)
{
	FoundAttributeModifier = nullptr;
	for (int32 i = 0; i < CreatedActiveAttributeModifiers.Num(); i++)
	{

		if (CreatedActiveAttributeModifiers[i])
		{
			if (CreatedActiveAttributeModifiers[i]->GetClass() == AttributeModifierToSearch)
			{
				FoundAttributeModifier = CreatedActiveAttributeModifiers[i];

				return;
			}
		}

	}

	FoundAttributeModifier = nullptr;
	return;
}

UAttributeBase* UAttributesComponent::GetAttributeOfGameplayTag(FGameplayTag AttributeGameplayTag)
{

	UAttributeBase* LocalAttribute = nullptr;
	for (int32 i = 0; i < CreatedAttributes.Num(); i++)
	{
		if (CreatedAttributes[i])
		{
			if (CreatedAttributes[i]->AttributeGameplayTag == AttributeGameplayTag)
			{
				LocalAttribute = CreatedAttributes[i];
				return LocalAttribute;
			}
		}
	}

	return LocalAttribute;
}

void UAttributesComponent::RemoveFromActiveAttributeModifiers(UAttributeModifier* AttributeModifierToRemove)
{
	if (AttributeModifierToRemove)
	{
		CreatedActiveAttributeModifiers.Remove(AttributeModifierToRemove);
	}
}

void UAttributesComponent::AddToActiveAttributeModifiers(UAttributeModifier* AttributeModifierToAdd)
{
	if (AttributeModifierToAdd)
	{
		CreatedActiveAttributeModifiers.Add(AttributeModifierToAdd);
	}
}

void UAttributesComponent::ConstructAttributeModifierOfClass(TSubclassOf<UAttributeModifier> AttributeModifierToConstruct, FAttributeModifierProperties ModiferProperties, UAttributeModifier*& ConstructedAttributeModifier)
{
	ConstructedAttributeModifier = nullptr;

	if (AttributeModifierToConstruct)
	{
		UAttributeModifier* LocalNewAttributeModifier;
		LocalNewAttributeModifier = NewObject<UAttributeModifier>(GetOwner(), AttributeModifierToConstruct);
		LocalNewAttributeModifier->ModiferProperties = ModiferProperties;
		LocalNewAttributeModifier->ConstructAttributeModifier();
		ConstructedAttributeModifier = LocalNewAttributeModifier;
	}
}

