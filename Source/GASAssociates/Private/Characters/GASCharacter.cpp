// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GASCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Components/GAAbilitySystemComponent.h"

FName AGASCharacter::AbilitySystemComponentName = TEXT("AbilitySystemComponent");

// Sets default values
AGASCharacter::AGASCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UGAAbilitySystemComponent>(this, AbilitySystemComponentName);
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void AGASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AddAttributes();
}

void AGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo(this, this);
	AddAttributes();
	AddStartupEffects();
	AddAbilities();
}

void AGASCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	InitAbilityActorInfo(this, this);
}

void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(IsValid(GetAbilitySystemComponent()))
	{
		GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("EAbilityInput"), static_cast<int32>(EAbilityInput::Confirm), static_cast<int32>(EAbilityInput::Cancel)));
	}
}