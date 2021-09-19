// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_BaseGameplayerEffectAppliedToSelf.h"

#include "AbilitySystemComponent.h"

void UAsyncAction_BaseGameplayerEffectAppliedToSelf::Activate()
{
	Super::Activate();

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this,
			&ThisClass::OnActiveGameplayEffectAddedToSelfCallback);
		AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(this,
			&ThisClass::OnActiveGameplayEffectRemovedCallback);
	}
	else
	{
		EndTask();
	}
}

void UAsyncAction_BaseGameplayerEffectAppliedToSelf::EndTask_Implementation()
{
	Super::EndTask_Implementation();

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
	}
}
