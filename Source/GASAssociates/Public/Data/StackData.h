// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "StackData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct GASASSOCIATES_API FStackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NewStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PreviousStackCount;
};
