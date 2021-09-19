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

// Called when the game starts or when spawned
void APSGASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool APSGASCharacter::CanInitAbilityActorInfo() const
{
	APlayerState* CurrentPlayerState = GetPlayerState();
	return IsValid(CurrentPlayerState) && Cast<IAbilitySystemInterface>(CurrentPlayerState) && !IsAbilitySystemComponentWereInitialized();
}

void APSGASCharacter::InitAbilityActorInfo()
{
	if (CanInitAbilityActorInfo())
	{
		if (const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPlayerState()))
		{
			AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
			GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
			bAbilitySystemComponentWereInitialized = true;
		}
	}
}

void APSGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void APSGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddAttributes();
	AddStartupEffects();
	AddAbilities();
}

void APSGASCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	/*
	InitAbilityActorInfo();
	AddAttributes();*/
}


// Called to bind functionality to input
void APSGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APSGASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
