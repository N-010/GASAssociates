// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryDataAssets/PrimaryDataAssetWithTag.h"

void UPrimaryDataAssetWithTag::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
{
	Super::GetAssetRegistryTags(OutTags);

	OutTags.Add(
		FAssetRegistryTag(GET_MEMBER_NAME_CHECKED(ThisClass, TagContainer), TagContainer.ToString(), FAssetRegistryTag::TT_Hidden));
}
