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
	
public:
	bool IsStartupEffectsApplied() const;
	bool IsAbilitySystemComponentWereInitialized() const;
	bool IsAbilitiesWereAdded() const;
};
