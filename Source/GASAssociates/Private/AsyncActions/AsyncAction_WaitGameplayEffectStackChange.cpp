// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_WaitGameplayEffectStackChange.h"

#include "AbilitySystemComponent.h"

UAsyncAction_WaitGameplayEffectStackChange* UAsyncAction_WaitGameplayEffectStackChange::WaitForGameplayEffectStackChange(
	UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayTagContainer& InGameplayTagContainer)
{
	UAsyncAction_WaitGameplayEffectStackChange* AsyncAction = nullptr;
	if (IsValid(InAbilitySystemComponent))
	{
		AsyncAction = NewObject<UAsyncAction_WaitGameplayEffectStackChange>();
		if (AsyncAction)
		{
			AsyncAction->RegisterWithGameInstance(InAbilitySystemComponent);
			AsyncAction->AbilitySystemComponent = InAbilitySystemComponent;
			AsyncAction->GameplayTagContainer = InGameplayTagContainer;
		}
	}

	return AsyncAction;
}


void UAsyncAction_WaitGameplayEffectStackChange::Activate()
{
	Super::Activate();

	if (!AbilitySystemComponent.IsValid() || GameplayTagContainer.IsEmpty())
	{
		EndTask();
		return;
	}

	TArray<FActiveGameplayEffectHandle> ActiveEffects = AbilitySystemComponent->GetActiveEffectsWithAllTags(GameplayTagContainer);
	for (const auto& ActiveEffect : ActiveEffects)
	{
		ListenForStackChanges(ActiveEffect);
	}
}

void UAsyncAction_WaitGameplayEffectStackChange::EndTask_Implementation()
{
	Super::EndTask_Implementation();
}

bool UAsyncAction_WaitGameplayEffectStackChange::IsHasAnyExact(const FGameplayEffectSpec& Spec) const
{
	FGameplayTagContainer SpecTags;
	Spec.GetAllAssetTags(SpecTags);

	return GameplayTagContainer.HasAnyExact(SpecTags);
}

void UAsyncAction_WaitGameplayEffectStackChange::OnActiveGameplayEffectAddedToSelfCallback(
	UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	if (IsHasAnyExact(Spec))
	{
		OnGameplayStackChange(Handle, 1, 0);
		ListenForStackChanges(Handle);
	}
}

void UAsyncAction_WaitGameplayEffectStackChange::OnActiveGameplayEffectRemovedCallback(
	const FActiveGameplayEffect& ActiveGameplayEffect)
{
	const FActiveGameplayEffectHandle& Handle = ActiveGameplayEffect.Handle;
	if (GameplayStackChangeHandleMap.Find(Handle))
	{
		OnGameplayStackChange(Handle, 0, 1);
		GameplayStackChangeHandleMap.Remove(Handle);
	}
}

void UAsyncAction_WaitGameplayEffectStackChange::OnGameplayStackChange(FActiveGameplayEffectHandle ActiveGameplayEffectHandle,
	int32 NewStackCount, int32 PreviousStackCount) const
{
	if (OnGameplayEffectStackChange.IsBound())
	{
		OnGameplayEffectStackChange.Broadcast(FStackData{ActiveGameplayEffectHandle, NewStackCount, PreviousStackCount});
	}
}

void UAsyncAction_WaitGameplayEffectStackChange::ListenForStackChanges(const FActiveGameplayEffectHandle& ActiveEffect)
{
	if(GameplayStackChangeHandleMap.Find(ActiveEffect))
	{
		return;
	}
	
	if (FOnActiveGameplayEffectStackChange* GameplayEffectStackChangeHandle = AbilitySystemComponent->
		OnGameplayEffectStackChangeDelegate(ActiveEffect))
	{
		FDelegateHandle DelegateHandle = GameplayEffectStackChangeHandle->AddUObject(
			this, &ThisClass::OnGameplayStackChange);
		if (DelegateHandle.IsValid())
		{
			GameplayStackChangeHandleMap.Add(ActiveEffect, MoveTemp(DelegateHandle));
		}
	}
}
