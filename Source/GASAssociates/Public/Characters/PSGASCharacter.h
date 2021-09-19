// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GABaseCharacter.h"
#include "PSGASCharacter.generated.h"

UCLASS()
class GASASSOCIATES_API APSGASCharacter : public AGABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APSGASCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//~ Begin GASBaseCharacter Interfaces
	virtual bool CanInitAbilityActorInfo() const override;
	virtual void InitAbilityActorInfo() override;
	//~ End GASBaseCharacter Interfaces

	//~ Begin APlayerState Interfaces
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	//~ End APlayerState Interfaces
	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	//~ Begin APawn Interfaces
	virtual void PostInitializeComponents() override;
	//~ End APawn Interfaces
};
