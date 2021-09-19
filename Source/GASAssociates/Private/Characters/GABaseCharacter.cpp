// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GABaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Attributes/BaseAttributeSet.h"
#include "Components/GAAbilitySystemComponent.h"


// Sets default values
AGABaseCharacter::AGABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool AGABaseCharacter::IsAbilitiesWereAdded() const
{
	return bAbilitiesWereAdded;
}

bool AGABaseCharacter::IsAlive() const
{
	bool bIsAlive = false;

	if (GetBaseAttributeSet())

	{
		bIsAlive = GetBaseAttributeSet()->GetHealth() > 0.f;
	}

	return bIsAlive;
}

UGAAbilitySystemComponent* AGABaseCharacter::GetGAAbilitySystemComponent() const
{
	return IsValid(GetAbilitySystemComponent()) ? Cast<UGAAbilitySystemComponent>(GetAbilitySystemComponent()) : nullptr;
}

int32 AGABaseCharacter::GetCharacterLevel() const
{
	return 1;
}

UAbilitySystemComponent* AGABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGABaseCharacter::InitAbilityActorInfo()
{
	if (CanInitAbilityActorInfo())
	{
		GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
		bAbilitySystemComponentWereInitialized = true;
	}
}

bool AGABaseCharacter::IsAbilitySystemComponentWereInitialized() const
{
	return bAbilitySystemComponentWereInitialized;
}

bool AGABaseCharacter::CanInitAbilityActorInfo() const
{
	return IsValid(GetAbilitySystemComponent()) && !IsAbilitySystemComponentWereInitialized();
}

bool AGABaseCharacter::AddStartupEffects()
{
	if (IsValid(GetAbilitySystemComponent()) && !bStartupEffectsApplied && GetLocalRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		for (const auto& StartupEffect : StartupEffects)
		{
			FGameplayEffectSpecHandle GameplayEffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(StartupEffect,
				GetCharacterLevel(),
				EffectContext);
			if (GameplayEffectSpec.IsValid())
			{
				GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpec.Data.Get(),
					GetAbilitySystemComponent());
			}
		}

		bStartupEffectsApplied = true;

		return true;
	}

	return false;
}

const UAttributeSet* AGABaseCharacter::GetAttributeSet() const
{
	if (UGAAbilitySystemComponent* GAAbilitySystemComponent = GetGAAbilitySystemComponent())
	{
		return GAAbilitySystemComponent->SpawnedAttributes.Num() > 0 ? GAAbilitySystemComponent->SpawnedAttributes[0] : nullptr;
	}

	return nullptr;
}


UAttributeSet* AGABaseCharacter::GetAttributeSet()
{
	return const_cast<UAttributeSet*>(static_cast<const AGABaseCharacter*>(this)->GetAttributeSet());
}

const UBaseAttributeSet* AGABaseCharacter::GetBaseAttributeSet() const
{
	return Cast<UBaseAttributeSet>(GetAttributeSet());
}

UBaseAttributeSet* AGABaseCharacter::GetBaseAttributeSet()
{
	return const_cast<UBaseAttributeSet*>(static_cast<const AGABaseCharacter*>(this)->GetBaseAttributeSet());
}

void AGABaseCharacter::AddAbilities()
{
	if (UGAAbilitySystemComponent* GAAbilitySystemComponent = GetGAAbilitySystemComponent())
	{
		GAAbilitySystemComponent->AddAbilities(Abilities, GetCharacterLevel());
	}
}

void AGABaseCharacter::AddAttributes()
{
	if (UGAAbilitySystemComponent* GAAbilitySystemComponent = GetGAAbilitySystemComponent())
	{
		AttributeSet = const_cast<UAttributeSet*>(GAAbilitySystemComponent->AddAttributes(AttributeSetClass, nullptr));
	}
}

void AGABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	BP_OnRepPlayerState();
}

void AGABaseCharacter::UnPossessed()
{
	Super::UnPossessed();
	BP_OnRepPlayerState();
}

void AGABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	BP_OnRepPlayerState();
}
