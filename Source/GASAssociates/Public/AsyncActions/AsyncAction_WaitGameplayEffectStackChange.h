// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AsyncAction_BaseGameplayerEffectAppliedToSelf.h"
#include "Data/StackData.h"
#include "AsyncAction_WaitGameplayEffectStackChange.generated.h"

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectStackChange, FStackData, StackData);

/**
 * 
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy=AsyncTask), Transient)
class GASASSOCIATES_API UAsyncAction_WaitGameplayEffectStackChange final : public UAsyncAction_BaseGameplayerEffectAppliedToSelf
{
	GENERATED_BODY()

private:
	FGameplayTagContainer GameplayTagContainer;

private:
	TMap<FActiveGameplayEffectHandle, FDelegateHandle> GameplayStackChangeHandleMap;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameplayEffectStackChange OnGameplayEffectStackChange;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncAction_WaitGameplayEffectStackChange* WaitForGameplayEffectStackChange(
		UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayTagContainer& InGameplayTagContainer);

	virtual void Activate() override;
	virtual void EndTask_Implementation() override;
	bool IsHasAnyExact(const FGameplayEffectSpec& Spec) const;

private:
	virtual void OnActiveGameplayEffectAddedToSelfCallback(UAbilitySystemComponent* InAbilitySystemComponent,
		const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle) override;
	virtual void OnActiveGameplayEffectRemovedCallback(const FActiveGameplayEffect& ActiveGameplayEffect) override;

	void OnGameplayStackChange(FActiveGameplayEffectHandle ActiveGameplayEffectHandle, int32 NewStackCount,
		int32 PreviousStackCount) const;

private:
	void ListenForStackChanges(const FActiveGameplayEffectHandle& ActiveEffect);
};
