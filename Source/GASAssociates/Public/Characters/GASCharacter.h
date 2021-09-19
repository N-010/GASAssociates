// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GABaseCharacter.h"
#include "GASCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UBaseAttributeSet;

UCLASS()
class GASASSOCIATES_API AGASCharacter : public AGABaseCharacter
{
	GENERATED_BODY()

public:
	static FName AbilitySystemComponentName;

public:
	// Sets default values for this character's properties
	AGASCharacter(const FObjectInitializer& ObjectInitializer);

	//~ Begin UObject Interfaces
	virtual void PostInitializeComponents() override;
	//~ End UObject Interfaces

	//~ Begin APawn Interfaces
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	//~ End APawn Interfaces
	
};
