// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASBlueprintLibrary.generated.h"

class UAbilitySystemComponent;
struct FGameplayAbilitySpec;
struct FGameplayTagContainer;

/**
 * 
 */
UCLASS(meta=(ScriptName="GASAssociatesLibrary"))
class GASASSOCIATES_API UGASBlueprintLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Ability")
	static void GetActivatableAbilities(const UAbilitySystemComponent* AbilitySystemComponent,
		TArray<FGameplayAbilitySpec>& ActivatableAbilities);

	UFUNCTION(BlueprintCallable, Category="Ability")
	static void GetActivatableGameplayAbilitySpecsByAllMatchingTags(const UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayTagContainer& GameplayTagContainer, TArray<FGameplayAbilitySpec>& MatchingGameplayAbilities,
		const bool bOnlyAbilitiesThatSatisfyTagRequirements = true);

	UFUNCTION(BlueprintPure, Category="Ability")
	static bool IsAbilityActive(const FGameplayAbilitySpec& AbilitySpec);
};
