// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define DECLARE_ONREP_FUNCTION(ClassName, PropertyName)\
	void ClassName::OnRep_##PropertyName(const FGameplayAttributeData& OldValue)\
	{\
		GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue);\
	}


class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class GASASSOCIATES_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(Health)

	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(Armor)

	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing=OnRep_MaxArmor)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(MaxArmor)
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing=OnRep_APReduce)
	FGameplayAttributeData APReduce;
	ATTRIBUTE_ACCESSORS(APReduce)
	
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing=OnRep_WalkSpeed)
	FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(WalkSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing=OnRep_WalkSpeedCrouched)
	FGameplayAttributeData WalkSpeedCrouched;
	ATTRIBUTE_ACCESSORS(WalkSpeedCrouched)

	// Meta Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(Damage)

public:
	UBaseAttributeSet(const FObjectInitializer& ObjectInitializer);

	//~ Begin UObject
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~ End UObject

	//~ Begin UAttributeSet
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	//~ End UAttributeSet

	virtual void SetCurrentToBaseValues();

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	virtual void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute,
		const float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxArmor(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_APReduce(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_WalkSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_WalkSpeedCrouched(const FGameplayAttributeData& OldValue);

protected:
	virtual void ApplyDamage(const FGameplayEffectModCallbackData& Data);
	virtual void ApplyWalkSpeed(const FGameplayEffectModCallbackData& Data);
	virtual void ApplyWalkSpeedCrouched(const FGameplayEffectModCallbackData& Data);

	virtual void OnDead(const FGameplayEffectModCallbackData& Data);
	
	virtual UCharacterMovementComponent* GetTargetCharacterMovement(const FGameplayEffectModCallbackData& Data) const;
	virtual UCharacterMovementComponent* GetCharacterMovement() const;
};
