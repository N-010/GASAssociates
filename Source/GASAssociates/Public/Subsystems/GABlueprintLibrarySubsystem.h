// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "GABlueprintLibrarySubsystem.generated.h"

/**
 * 
 */
UCLASS(DisplayName="GABlueprintLibrarySubsystem", Category="GASAssociates")
class GASASSOCIATES_API UGABlueprintLibrarySubsystem final : public USubsystemBlueprintLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"), Category="GASAssociates")
	static void GetAllAlivePlayerStates(UObject* WorldContextObject, TArray<APlayerState*>& PlayerStates);
};
