// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GAAbilitySystemComponent.h"

#include "Abilities/BaseGameplayAbility.h"


// Sets default values for this component's properties
UGAAbilitySystemComponent::UGAAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGAAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	if (IsAbilitySystemComponentWereInitialized())
	{
		return;
	}

	/** UnRegister can be called to reuse the component on a new avatar.
	 *	To do this you have to call the OnRegister component again
	 */
	if (!IsRegistered())
	{
		OnRegister();
	}

	if (!HasBeenInitialized() && bWantsInitializeComponent)
	{
		InitializeComponent();
	}

	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
}

const UAttributeSet* UGAAbilitySystemComponent::AddAttributes(TSubclassOf<UAttributeSet> Attributes, const UDataTable* DataTable)
{
	if (*Attributes == nullptr)
	{
		return nullptr;
	}

	const UAttributeSet* AttributeSet = InitStats(Attributes, nullptr);
	ForceReplication();
	ForceAvatarReplication();

	return AttributeSet;
}

void UGAAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, const int32& Level)
{
	if (!GetOwner()->HasAuthority() || IsAbilitiesWereAdded())
	{
		return;
	}

	if (!IsValid(GetAvatarActor()))
	{
		UE_LOG(LogAbilitySystemComponent, Error, TEXT("UGAAbilitySystemComponent::AddAbilities: Avatar not set"));
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		int32 InputID = INDEX_NONE;
		if (const UBaseGameplayAbility* CDO = Cast<UBaseGameplayAbility>(Ability.GetDefaultObject()))
		{
			EAbilityInput AbilityInput = CDO->GetInputID();
			InputID = AbilityInput != EAbilityInput::None ? static_cast<int32>(AbilityInput) : INDEX_NONE;
		}
		if (!GiveAbility(FGameplayAbilitySpec(Ability, Level, InputID, this)).IsValid())
		{
			UE_LOG(LogAbilitySystemComponent, Error, TEXT("UGAAbilitySystemComponent::AddAbilities: GiveAbility: %s Is Not Valid"),
				*Ability->GetFName().ToString());
		}
	}

	bAbilitiesWereAdded = true;
}

bool UGAAbilitySystemComponent::AddStartupEffects(const TArray<TSubclassOf<UGameplayEffect>>& StartupEffects,
	const int32& CharacterLevel)
{
	if (!IsStartupEffectsApplied() && GetOwnerRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = MakeEffectContext();
		EffectContext.AddSourceObject(this);
		for (const auto& StartupEffect : StartupEffects)
		{
			FGameplayEffectSpecHandle GameplayEffectSpec = MakeOutgoingSpec(StartupEffect,
				CharacterLevel,
				EffectContext);
			if (GameplayEffectSpec.IsValid())
			{
				ApplyGameplayEffectSpecToTarget(*GameplayEffectSpec.Data.Get(), this);
			}
		}

		bStartupEffectsApplied = true;
	}

	return IsStartupEffectsApplied();
}

void UGAAbilitySystemComponent::OnUnregister()
{
	Super::OnUnregister();

	bStartupEffectsApplied = false;
	bAbilitySystemComponentWereInitialized = false;
	bAbilitiesWereAdded = false;
}

bool UGAAbilitySystemComponent::IsStartupEffectsApplied() const
{
	return bStartupEffectsApplied;
}

bool UGAAbilitySystemComponent::IsAbilitySystemComponentWereInitialized() const
{
	return bAbilitySystemComponentWereInitialized;
}

void UGAAbilitySystemComponent::MarkAsInitialized()
{
	bAbilitySystemComponentWereInitialized = true;
}

bool UGAAbilitySystemComponent::IsAbilitiesWereAdded() const
{
	return bAbilitiesWereAdded;
}
