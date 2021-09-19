// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BaseAsyncAction.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GASASSOCIATES_API UBaseAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	virtual void EndTask_Implementation();
};
