// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/BaseGameplayAbility.h"

#include "AbilitySystemComponent.h"

UBaseGameplayAbility::UBaseGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIsPassive(false)
{
}

bool UBaseGameplayAbility::IsPassive() const
{
	return bIsPassive;
}

void UBaseGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bIsPassive && ActorInfo && ActorInfo->AbilitySystemComponent.IsValid() && !Spec.IsActive())
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

const EAbilityInput& UBaseGameplayAbility::GetInputID() const
{
	return InputId;
}

#if WITH_EDITOR
bool UBaseGameplayAbility::CanEditChange(const FProperty* InProperty) const
{
	const bool bSuperCanEdit = Super::CanEditChange(InProperty);
	/*const FName PropertyName = !!InProperty ? InProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, bResetPassiveAbilityAfterDie))
	{
		return bSuperCanEdit && bIsPassive;
	}*/

	return bSuperCanEdit;
}
#endif // WITH_EDITOR
