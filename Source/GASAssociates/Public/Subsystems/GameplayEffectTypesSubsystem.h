// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "GameplayEffectTypesSubsystem.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
struct FGameplayTagContainer;
struct FGameplayEffectSpec;
struct FActiveGameplayEffectHandle;
/**
 * 
 */
UCLASS(Category="GASAssociates")
class GASASSOCIATES_API UGameplayEffectTypesSubsystem final : public USubsystemBlueprintLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="GASAssociates|Spec|Duration")
	static float GetDuration(const FGameplayEffectSpec& Spec);

	UFUNCTION(BlueprintCallable, Category="GASAssociates|Spec|Tag")
	static void GetAllGrantedTags(const FGameplayEffectSpec& Spec, FGameplayTagContainer& Container);

	UFUNCTION(BlueprintCallable, Category="GASAssociates|Spec|Tag")
	static void GetAllAssetTags(const FGameplayEffectSpec& Spec, FGameplayTagContainer& Container);

	UFUNCTION(BlueprintPure, CustomThunk, Category="GASAssociates|Spec")
	static const UGameplayEffect* GetGameplayEffectDefForSpec(const FGameplayEffectSpec& Spec);
	DECLARE_FUNCTION(execGetGameplayEffectDefForSpec);

	UFUNCTION(BlueprintCallable, Category="GASAssociates|Handle")
	static FGameplayEffectSpec GetGameplayEffectSpecFromActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);

	UFUNCTION(BlueprintPure, CustomThunk, Category="GASAssociates|Handle")
	static const UAbilitySystemComponent* GetAbilitySystemComponentFromHandle(const FActiveGameplayEffectHandle& Handle);
	DECLARE_FUNCTION(execGetAbilitySystemComponentFromHandle);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (ActiveGameplayEffectHandle)", CompactNodeTitle = "==", Keywords = "== equal"), Category="GASAssociates|Handle")
	static bool EqualEqual_ActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& A, const FActiveGameplayEffectHandle& B);
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="IsValid (ActiveGameplayEffectHandle)", CompactNodeTitle="IsValid?"), Category="GASAssociates|Handle")
	static bool IsValid_ActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& A);
};
