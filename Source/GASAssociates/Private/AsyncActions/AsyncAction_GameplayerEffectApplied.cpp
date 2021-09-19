// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_GameplayerEffectApplied.h"

#include "AbilitySystemComponent.h"

UAsyncAction_GameplayerEffectApplied* UAsyncAction_GameplayerEffectApplied::ListenForGameplayerEffectApply(
	UAbilitySystemComponent* InAbilitySystemComponent)
{
	if (!IsValid(InAbilitySystemComponent))
	{
		return nullptr;
	}

	UAsyncAction_GameplayerEffectApplied* AsyncAction = NewObject<UAsyncAction_GameplayerEffectApplied>();
	if (IsValid(AsyncAction))
	{
		AsyncAction->RegisterWithGameInstance(InAbilitySystemComponent);
		AsyncAction->AbilitySystemComponent = InAbilitySystemComponent;
	}

	return AsyncAction;
}

void UAsyncAction_GameplayerEffectApplied::OnActiveGameplayEffectAddedToSelfCallback(
	UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	if (AppliedToSelf.IsBound())
	{
		AppliedToSelf.Broadcast(Spec);
	}
}

void UAsyncAction_GameplayerEffectApplied::OnActiveGameplayEffectRemovedCallback(const FActiveGameplayEffect& ActiveGameplayEffect)
{
	if (RemoveToSelf.IsBound())
	{
		RemoveToSelf.Broadcast(ActiveGameplayEffect.Spec);
	}
}