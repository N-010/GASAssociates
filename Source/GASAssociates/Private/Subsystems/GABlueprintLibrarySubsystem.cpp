// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GABlueprintLibrarySubsystem.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Characters/GABaseCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UGABlueprintLibrarySubsystem::GetAllAlivePlayerStates(UObject* WorldContextObject, TArray<APlayerState*>& PlayerStates)
{
	if (IsValid(WorldContextObject))
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		const AGameStateBase* GameState = IsValid(World) ? World->GetGameState() : nullptr;
		if (IsValid(GameState))
		{
			for (APlayerState* const PlayerState : GameState->PlayerArray)
			{
				if (IsValid(PlayerState) && !PlayerState->IsABot())
				{
					const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(PlayerState);
					if (!AbilitySystemInterface)
					{
						AbilitySystemInterface = Cast<IAbilitySystemInterface>(PlayerState->GetOwner());
					}

					if (AbilitySystemInterface)
					{
						const UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
						if (IsValid(AbilitySystemComponent))
						{
							AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
							const AGABaseCharacter* BaseCharacter = IsValid(AvatarActor)
								                                        ? Cast<AGABaseCharacter>(AvatarActor)
								                                        : nullptr;
							if (IsValid(BaseCharacter) && BaseCharacter->IsAlive())
							{
								PlayerStates.Add(PlayerState);
							}
						}
					}
				}
			}
		}
	}
}
