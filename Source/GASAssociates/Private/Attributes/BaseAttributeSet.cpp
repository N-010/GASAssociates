// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/BaseAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Characters/GASCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

DECLARE_ONREP_FUNCTION(UBaseAttributeSet, Health)
DECLARE_ONREP_FUNCTION(UBaseAttributeSet, MaxHealth)
DECLARE_ONREP_FUNCTION(UBaseAttributeSet, Armor)
DECLARE_ONREP_FUNCTION(UBaseAttributeSet, MaxArmor)
DECLARE_ONREP_FUNCTION(UBaseAttributeSet, APReduce)

void UBaseAttributeSet::OnRep_WalkSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, WalkSpeed, OldValue);

	if (IsValid(GetCharacterMovement()))
	{
		GetCharacterMovement()->MaxWalkSpeed = GetWalkSpeed();
	}
}

void UBaseAttributeSet::OnRep_WalkSpeedCrouched(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, WalkSpeedCrouched, OldValue);

	if (IsValid(GetCharacterMovement()))
	{
		GetCharacterMovement()->MaxWalkSpeedCrouched = GetWalkSpeedCrouched();
	}
}

UBaseAttributeSet::UBaseAttributeSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Health(1.f)
	, MaxHealth(1.f)
	, Armor(0.f)
	, MaxArmor(0.f)
	, APReduce(1.f)
	, WalkSpeed(600.f)
	, WalkSpeedCrouched(WalkSpeed.GetBaseValue() * 0.5)
	, Damage(0.f)
{
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, APReduce, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, WalkSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, WalkSpeedCrouched, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxArmorAttribute())
	{
		AdjustAttributeForMaxChange(Armor, MaxArmor, NewValue, GetArmorAttribute());
	}
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

	if (Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		if (GetHealth() <= 0.f)
		{
			OnDead(Data);
		}
	}
	else if (Attribute == GetDamageAttribute())
	{
		ApplyDamage(Data);
	}
	else if (Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(), 0.f, GetMaxArmor()));
	}
	else if (Attribute == GetAPReduceAttribute())
	{
		SetAPReduce(FMath::Clamp(GetAPReduce(), 0.f, 1.f));
	}
	else if (Attribute == GetWalkSpeedAttribute())
	{
		ApplyWalkSpeed(Data);
	}
	else if (Attribute == GetWalkSpeedCrouchedAttribute())
	{
		ApplyWalkSpeedCrouched(Data);
	}
}

void UBaseAttributeSet::SetCurrentToBaseValues()
{
	for (TFieldIterator<FStructProperty> It(GetClass()); It; ++It)
	{
		if (FGameplayAttributeData* CurrentAttributeData = It->ContainerPtrToValuePtr<FGameplayAttributeData>(this))
		{
			CurrentAttributeData->SetCurrentValue(CurrentAttributeData->GetBaseValue());
		}
	}
}

void UBaseAttributeSet::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, const float NewMaxValue,
	const FGameplayAttribute& AffectedAttributeProperty) const
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = CurrentMaxValue > 0.f
			                       ? CurrentValue * NewMaxValue / CurrentMaxValue - CurrentValue
			                       : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}


void UBaseAttributeSet::ApplyDamage(const FGameplayEffectModCallbackData& Data)
{
	// Store a local copy of the amount of damage done and clear the damage attribute
	const float LocalDamageDone = GetDamage();
	float LocalDamageByHealth = LocalDamageDone;
	SetDamage(0.f);

	if (LocalDamageDone > 0.0f)
	{
		// Apply the damage to shield first if it exists
		const float OldArmor = GetArmor();
		if (OldArmor > 0)
		{
			LocalDamageByHealth = 0;

			const float LocalDamageDoneByArmor = LocalDamageDone * GetAPReduce();
			const float NewArmor = OldArmor - LocalDamageDoneByArmor;
			SetArmor(FMath::Clamp<float>(NewArmor, 0.0f, GetMaxArmor()));

			/** If the armor could not absorb all the damage */
			if (FMath::IsNearlyZero(NewArmor) || NewArmor < 0)
			{
				LocalDamageByHealth += FMath::Abs(NewArmor);
			}

			LocalDamageByHealth += LocalDamageDone - LocalDamageDoneByArmor;
		}
	}

	if (LocalDamageByHealth > 0)
	{
		// Apply the health change and then clamp it
		const float NewHealth = GetHealth() - LocalDamageByHealth;
		SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	}

	if (GetHealth() <= 0)
	{
		OnDead(Data);
	}
}

void UBaseAttributeSet::ApplyWalkSpeed(const FGameplayEffectModCallbackData& Data)
{
	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	if (Attribute != GetWalkSpeedAttribute())
	{
		return;
	}

	SetWalkSpeed(FMath::Max(GetWalkSpeed(), 0.f));

	UCharacterMovementComponent* AvatarMovementComponent = GetTargetCharacterMovement(Data);
	if (IsValid(AvatarMovementComponent))
	{
		AvatarMovementComponent->MaxWalkSpeed = GetWalkSpeed();
	}
}

void UBaseAttributeSet::ApplyWalkSpeedCrouched(const FGameplayEffectModCallbackData& Data)
{
	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	if (Attribute != GetWalkSpeedCrouchedAttribute())
	{
		return;
	}

	SetWalkSpeedCrouched(FMath::Max(GetWalkSpeedCrouched(), 0.f));

	UCharacterMovementComponent* AvatarMovementComponent = GetTargetCharacterMovement(Data);
	if (IsValid(AvatarMovementComponent))
	{
		AvatarMovementComponent->MaxWalkSpeedCrouched = GetWalkSpeedCrouched();
	}
}

void UBaseAttributeSet::OnDead(const FGameplayEffectModCallbackData& Data)
{
	const UAbilitySystemComponent* TargetASC = &Data.Target;
	if (AGABaseCharacter* TargetBaseCharacter = IsValid(TargetASC) ? Cast<AGABaseCharacter>(TargetASC->GetAvatarActor()) : nullptr)
	{
		TargetBaseCharacter->OnDead();
	}
}

UCharacterMovementComponent* UBaseAttributeSet::GetTargetCharacterMovement(const FGameplayEffectModCallbackData& Data) const
{
	const ACharacter* AvatarCharacter = IsValid(Data.Target.GetAvatarActor())
		                                    ? Cast<ACharacter>(Data.Target.GetAvatarActor())
		                                    : nullptr;
	return IsValid(AvatarCharacter)
		       ? AvatarCharacter->GetCharacterMovement()
		       : nullptr;
}

UCharacterMovementComponent* UBaseAttributeSet::GetCharacterMovement() const
{
	const AActor* Avatar = GetOwningAbilitySystemComponent()->GetAvatarActor();
	const ACharacter* AvatarCharacter = IsValid(Avatar)
		                                    ? Cast<ACharacter>(Avatar)
		                                    : nullptr;
	return IsValid(AvatarCharacter)
		       ? AvatarCharacter->GetCharacterMovement()
		       : nullptr;
}
