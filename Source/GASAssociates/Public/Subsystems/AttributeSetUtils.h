// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "AttributeSetUtils.generated.h"

class UAttributeSet;
struct FGameplayAttribute;
struct FGameplayAttributeData;
/**
 * 
 */
UCLASS()
class GASASSOCIATES_API UAttributeSetUtils : public USubsystemBlueprintLibrary
{
	GENERATED_BODY()
	
public:
	static void AdjustAttributeForMaxChange(const UAttributeSet* AttributeSet,
	                                        const FGameplayAttributeData& AffectedAttribute,
	                                        const FGameplayAttributeData& MaxAttribute,
	                                        const float NewMaxValue,
	                                        const FGameplayAttribute& AffectedAttributeProperty);
};
