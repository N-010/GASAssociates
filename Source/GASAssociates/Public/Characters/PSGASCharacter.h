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

	//~ Begin GASBaseCharacter Interfaces
protected:
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End GASBaseCharacter Interfaces

	//~ Begin APlayerState Interfaces
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	//~ End APlayerState Interfaces
};
