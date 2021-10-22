// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(AbilitySystem), meta=(BlueprintSpawnableComponent))
class GASASSOCIATES_API UGAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

private:
	bool bStartupEffectsApplied;
	bool bAbilitySystemComponentWereInitialized;
	bool bAbilitiesWereAdded;

public:
	// Sets default values for this component's properties
	UGAAbilitySystemComponent(const FObjectInitializer& ObjectInitializer);

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	virtual const UAttributeSet* AddAttributes(TSubclassOf<class UAttributeSet> Attributes, const UDataTable* DataTable);

	virtual void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, const int32& Level);

	virtual bool AddStartupEffects(const TArray<TSubclassOf<UGameplayEffect>>& StartupEffects, const int32& CharacterLevel);

	virtual void OnUnregister() override;

public:
	bool IsStartupEffectsApplied() const;
	bool IsAbilitySystemComponentWereInitialized() const;
	FORCEINLINE void MarkAsInitialized();
	bool IsAbilitiesWereAdded() const;
};
