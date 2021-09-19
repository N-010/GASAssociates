// Fill out your copyright notice in the Description page of Project Settings.


#include "GASBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


void UGASBlueprintLibrary::GetActivatableAbilities(const UAbilitySystemComponent* AbilitySystemComponent,
	TArray<FGameplayAbilitySpec>& ActivatableAbilities)
{
	if (IsValid(AbilitySystemComponent))
	{
		ActivatableAbilities = AbilitySystemComponent->GetActivatableAbilities();
	}
}

void UGASBlueprintLibrary::GetActivatableGameplayAbilitySpecsByAllMatchingTags(
	const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTagContainer& GameplayTagContainer,
	TArray<FGameplayAbilitySpec>& MatchingGameplayAbilities, const bool bOnlyAbilitiesThatSatisfyTagRequirements)
{
	if (IsValid(AbilitySystemComponent))
	{
		TArray<FGameplayAbilitySpec*> GameplayAbilities;
		AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, GameplayAbilities,
			bOnlyAbilitiesThatSatisfyTagRequirements);
		for (auto GameplayAbility : GameplayAbilities)
		{
			MatchingGameplayAbilities.Add(*GameplayAbility);
		}
	}
}

bool UGASBlueprintLibrary::IsAbilityActive(const FGameplayAbilitySpec& AbilitySpec)
{
	return AbilitySpec.IsActive();
}
