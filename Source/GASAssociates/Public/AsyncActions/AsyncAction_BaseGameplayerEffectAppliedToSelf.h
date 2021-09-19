// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAsyncAction.h"
#include "GameplayEffectTypes.h"
#include "AsyncAction_BaseGameplayerEffectAppliedToSelf.generated.h"

struct FGameplayEffectSpec;
struct FActiveGameplayEffect;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS(Abstract)
class GASASSOCIATES_API UAsyncAction_BaseGameplayerEffectAppliedToSelf : public UBaseAsyncAction
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	virtual void Activate() override;

protected:
	virtual void EndTask_Implementation() override;

private:
	virtual void OnActiveGameplayEffectAddedToSelfCallback(UAbilitySystemComponent* InAbilitySystemComponent,
		const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle) PURE_VIRTUAL(
		UAsyncAction_BaseGameplayerEffectAppliedToSelf::OnActiveGameplayEffectAddedToSelfCallback, return;);

	virtual void OnActiveGameplayEffectRemovedCallback(const FActiveGameplayEffect& ActiveGameplayEffect) PURE_VIRTUAL(
		UAsyncAction_BaseGameplayerEffectAppliedToSelf::OnActiveGameplayEffectRemovedCallback, return;);
};
