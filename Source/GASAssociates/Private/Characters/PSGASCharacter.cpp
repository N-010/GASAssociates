// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PSGASCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"


// Sets default values
APSGASCharacter::APSGASCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APSGASCharacter::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	AbilitySystemComponent = GetAbilitySystemComponent();
}

UAbilitySystemComponent* APSGASCharacter::GetAbilitySystemComponent() const
{
	APlayerState* CurrentPlayerState = GetPlayerState();
	IAbilitySystemInterface* AbilitySystemInterface = IsValid(CurrentPlayerState) ? Cast<IAbilitySystemInterface>(CurrentPlayerState) : nullptr;
	return AbilitySystemInterface ? AbilitySystemInterface->GetAbilitySystemComponent() : nullptr; 
}

void APSGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo(GetPlayerState(), this);
}

void APSGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo(GetPlayerState(), this);
	AddAttributes();
	AddStartupEffects();
	AddAbilities();
}