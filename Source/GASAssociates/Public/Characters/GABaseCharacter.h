// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Components/GAAbilitySystemComponent.h"
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

public:
	// Sets default values for this character's properties
	AGABaseCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category="Level")
	virtual int32 GetCharacterLevel() const;

	//~ Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	UGAAbilitySystemComponent* GetGAAbilitySystemComponent() const;

	UFUNCTION(BlueprintPure)
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintNativeEvent)
	void OnDead();

protected:
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor);

	virtual bool CanInitAbilityActorInfo() const;

	/**
	 * @brief Resetting a AbilitySystemComponent for later use on a new avatar or owner 
	 */
	virtual void UnRegisterAbilitySystemComponent();

	virtual bool AddStartupEffects();

	template <typename AttributeClass = UAttributeSet>
	const AttributeClass* GetAttributeSet() const;
	template <typename AttributeClass = UAttributeSet>
	AttributeClass* GetAttributeSet();

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
};

template<>
inline const UAttributeSet* AGABaseCharacter::GetAttributeSet<UAttributeSet>() const
{
	if (const UGAAbilitySystemComponent* GAAbilitySystemComponent = GetGAAbilitySystemComponent())
	{
		return GAAbilitySystemComponent->GetSpawnedAttributes().Num() > 0 ? GAAbilitySystemComponent->GetSpawnedAttributes()[0] : nullptr;
	}

	return nullptr;
}

template<>
inline UAttributeSet* AGABaseCharacter::GetAttributeSet()
{
	return const_cast<UAttributeSet*>(static_cast<const AGABaseCharacter*>(this)->GetAttributeSet<UAttributeSet>());
}

template <typename AttributeClass>
const AttributeClass* AGABaseCharacter::GetAttributeSet() const
{
	return Cast<AttributeClass>(GetAttributeSet());
}

template <typename AttributeClass>
AttributeClass* AGABaseCharacter::GetAttributeSet()
{
	return const_cast<AttributeClass*>(static_cast<const AGABaseCharacter*>(this)->GetAttributeSet<
		AttributeClass>());
}
