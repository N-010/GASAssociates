// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DataAssetSubsystem.h"
#include "PrimaryDataAssets/PrimaryDataAssetWithTag.h"
#include "Engine/AssetManager.h"

FPrimaryAssetId UDataAssetSubsystem::GetPrimaryAssetIdByTag(const FPrimaryAssetType PrimaryAssetType,
	const FGameplayTagContainer& TagContainer)
{
	FPrimaryAssetId FoundPrimaryAssetId;
	UAssetManager* AssetManager = PrimaryAssetType.IsValid() ? UAssetManager::GetIfValid() : nullptr;

	if (AssetManager)
	{
		TArray<FAssetData> AssetDataList;
		AssetManager->GetPrimaryAssetDataList(PrimaryAssetType, AssetDataList);
		FString Tags;
		for (const auto& AssetData : AssetDataList)
		{
			if (AssetData.IsValid())
			{
				AssetData.GetTagValue<FString>(GET_MEMBER_NAME_CHECKED(UPrimaryDataAssetWithTag, TagContainer), Tags);
				FGameplayTagContainer FoundTags;
				FoundTags.FromExportString(MoveTemp(Tags));
				if(FoundTags.HasAllExact(TagContainer))
				{
					FoundPrimaryAssetId = AssetData.GetPrimaryAssetId();
					break;
				}
			}
		}
	}

	return FoundPrimaryAssetId;
}
