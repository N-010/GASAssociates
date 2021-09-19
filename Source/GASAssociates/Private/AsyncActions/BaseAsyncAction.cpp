// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/BaseAsyncAction.h"

void UBaseAsyncAction::EndTask()
{
	EndTask_Implementation();
}

void UBaseAsyncAction::EndTask_Implementation()
{
	SetReadyToDestroy();
	MarkPendingKill();
}
