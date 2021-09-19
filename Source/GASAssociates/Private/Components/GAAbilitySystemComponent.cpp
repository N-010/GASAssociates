// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GAAbilitySystemComponent.h"

#include "Abilities/BaseGameplayAbility.h"


// Sets default values for this component's properties
UGAAbilitySystemComponent::UGAAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGAAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	if (AbilityActorInfo->AvatarActor == InAvatarActor && AbilityActorInfo->OwnerActor == InOwnerActor)
	{
	}
}

const UAttributeSet* UGAAbilitySystemComponent::AddAttributes(TSubclassOf<UAttributeSet> Attributes, const UDataTable* DataTable)
{
	if (*Attributes == nullptr)
	{
		return nullptr;
	}

	const UAttributeSet* AttributeSet = InitStats(Attributes, nullptr);
	ForceReplication();
	ForceAvatarReplication();

	return AttributeSet;
}

void UGAAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, const int32& Level)
{
	if (!GetOwner()->HasAuthority() || IsAbilitiesWereAdded())
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		int32 InputID = INDEX_NONE;
		if (const UBaseGameplayAbility* CDO = Cast<UBaseGameplayAbility>(Ability.GetDefaultObject()))
		{
			EAbilityInput AbilityInput = CDO->GetInputID();
			InputID = AbilityInput != EAbilityInput::None ? static_cast<int32>(AbilityInput) : INDEX_NONE;
		}
		GiveAbility(FGameplayAbilitySpec(Ability, Level, InputID, this));
	}

	bAbilitiesWereAdded = true;
}

bool UGAAbilitySystemComponent::IsStartupEffectsApplied() const
{
	return bStartupEffectsApplied;
}

bool UGAAbilitySystemComponent::IsAbilitySystemComponentWereInitialized() const
{
	return bAbilitySystemComponentWereInitialized;
}

bool UGAAbilitySystemComponent::IsAbilitiesWereAdded() const
{
	return bAbilitiesWereAdded;
}
