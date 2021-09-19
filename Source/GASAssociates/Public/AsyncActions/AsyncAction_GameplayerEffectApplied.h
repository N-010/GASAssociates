// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AsyncAction_BaseGameplayerEffectAppliedToSelf.h"
#include "BaseAsyncAction.h"
#include "GameplayEffect.h"
#include "AsyncAction_GameplayerEffectApplied.generated.h"

struct FActiveGameplayEffect;
struct FActiveGameplayEffectHandle;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectAppliedDelegate, const FGameplayEffectSpec&, Spec);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectRemoveDelegate, const FGameplayEffectSpec&, Spec);

/**
 * 
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy=AsyncTask))
class GASASSOCIATES_API UAsyncAction_GameplayerEffectApplied final : public UAsyncAction_BaseGameplayerEffectAppliedToSelf
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameplayEffectAppliedDelegate AppliedToSelf;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayEffectRemoveDelegate RemoveToSelf;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncAction_GameplayerEffectApplied* ListenForGameplayerEffectApply(UAbilitySystemComponent* InAbilitySystemComponent);

private:
	virtual void OnActiveGameplayEffectAddedToSelfCallback(UAbilitySystemComponent* InAbilitySystemComponent,
		const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle) override;
	virtual void OnActiveGameplayEffectRemovedCallback(const FActiveGameplayEffect& ActiveGameplayEffect) override;
};
