// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "DataAssetSubsystem.generated.h"

struct FGameplayTagContainer;

/**
 * 
 */
UCLASS(Category="GASAssociates")
class GASASSOCIATES_API UDataAssetSubsystem final : public USubsystemBlueprintLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="GASAssociates|DataAsset")
	static FPrimaryAssetId GetPrimaryAssetIdByTag(const FPrimaryAssetType PrimaryAssetType, const FGameplayTagContainer& TagContainer);

};
