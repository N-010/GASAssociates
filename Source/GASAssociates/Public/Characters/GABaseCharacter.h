// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GABaseCharacter.generated.h"

class UGAAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility;
class UAttributeSet;
class UBaseAttributeSet;

UCLASS(Abstract)
class GASASSOCIATES_API AGABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "True"), Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

protected:
	UPROPERTY()
	UAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"), Category = "Attribute")
	TSubclassOf<UAttributeSet> AttributeSetClass;

	bool bStartupEffectsApplied;
	bool bAbilitySystemComponentWereInitialized;
	bool bAbilitiesWereAdded;
	
public:
	UFUNCTION(BlueprintPure, Category="Level")
	virtual int32 GetCharacterLevel() const;

	//~ Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
	
	UGAAbilitySystemComponent* GetGAAbilitySystemComponent() const;

	bool IsAbilitySystemComponentWereInitialized() const;
	bool IsAbilitiesWereAdded() const;

	UFUNCTION(BlueprintPure)
	virtual  bool IsAlive() const;

protected:
	virtual void InitAbilityActorInfo();

	virtual bool CanInitAbilityActorInfo() const;

	virtual bool AddStartupEffects();

	const UAttributeSet* GetAttributeSet() const;
	UAttributeSet* GetAttributeSet();
	
	const UBaseAttributeSet* GetBaseAttributeSet() const;
	UBaseAttributeSet* GetBaseAttributeSet();

	virtual void AddAbilities();

	virtual void AddAttributes();
	
	//~ Begin APawn Interfaces
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_PlayerState() override;
	//~ End APawn Interfaces

	/**
	 * @brief PlayerState Replication Notification Callback 
	 */
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnRep_PlayerState"))
	void BP_OnRepPlayerState();

	/**
	 * @brief Called after AGABaseCharacter::InitAbilityActorInfo
	 */
	UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="BP_OnAfterInitAbilityActor"), Category = "Abilities")
	void BP_OnAfterInitAbilityActor();

public:
	// Sets default values for this character's properties
	AGABaseCharacter(const FObjectInitializer& ObjectInitializer);
};
