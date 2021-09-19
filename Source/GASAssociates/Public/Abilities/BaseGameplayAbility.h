// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/AbilityInput.h"

#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASASSOCIATES_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseGameplayAbility(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	bool bIsPassive;

private:
	/*/**
	 * @brief If true, it will remotely activate local/server abilities, if false it will only try to locally activate the ability
	 #1#
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	bool bAllowRemoteActivation;*/

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	EAbilityInput InputId;

public:
	//~ Begin UGameplayAbility Interfaces
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	//~ End UGameplayAbility Interfaces

	const EAbilityInput& GetInputID() const;

	bool IsPassive() const;

	//~ Begin UObject Interfaces
#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif // WITH_EDITOR
	//~ End UObject Interfaces
};
