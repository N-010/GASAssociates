// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GASPlayerState.generated.h"

enum class EGameplayEffectReplicationMode : uint8;
class UGAAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GASASSOCIATES_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;

protected:
	/**
	 * @brief Set the replication mode for the AbilitySystemComponent. Constructor only
	 */
	void SetReplicationMode(const EGameplayEffectReplicationMode& NewReplicationMode);

public:
	static FName AbilitySystemComponentName;
	static FName AttributeSetName;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="True"), Category="AbilitySystem")
	UGAAbilitySystemComponent* AbilitySystemComponent = nullptr;
};
