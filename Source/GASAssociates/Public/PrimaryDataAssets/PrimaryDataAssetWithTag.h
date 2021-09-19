// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "PrimaryDataAssetWithTag.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GASASSOCIATES_API UPrimaryDataAssetWithTag : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTagContainer TagContainer;

public:
	//~ Begin UObject
	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	//~ End UObject
};
