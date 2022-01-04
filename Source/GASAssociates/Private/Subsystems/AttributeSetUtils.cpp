// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AttributeSetUtils.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"


void UAttributeSetUtils::AdjustAttributeForMaxChange(const UAttributeSet* AttributeSet,
                                                     const FGameplayAttributeData& AffectedAttribute,
                                                     const FGameplayAttributeData& MaxAttribute,
                                                     const float NewMaxValue,
                                                     const FGameplayAttribute& AffectedAttributeProperty)
{
	if (!IsValid(AttributeSet))
	{
		//TODO: UE_LOG
		return;
	}
	
	UAbilitySystemComponent* AbilityComp = AttributeSet->GetOwningAbilitySystemComponent();
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
