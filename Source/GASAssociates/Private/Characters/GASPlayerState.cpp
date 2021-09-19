// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GASPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Components/GAAbilitySystemComponent.h"

FName AGASPlayerState::AbilitySystemComponentName(TEXT("AbilSystComp"));
FName AGASPlayerState::AttributeSetName(TEXT("AttributeSet"));

AGASPlayerState::AGASPlayerState(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UGAAbilitySystemComponent>(this, AbilitySystemComponentName);
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	NetUpdateFrequency = 3.f;
}


UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AGASPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGASPlayerState::SetReplicationMode(const EGameplayEffectReplicationMode& NewReplicationMode)
{
	const auto& ThreadContext = FUObjectThreadContext::Get();
	UE_CLOG(!ThreadContext.IsInConstructor, LogUObjectGlobals, Fatal, TEXT("AGASPlayerState::SetReplicationMode can't be used outside of constructors to find"));
	ensureAlways(ThreadContext.IsInConstructor);
	
	if(ThreadContext.IsInConstructor)
	{
		AbilitySystemComponent->SetReplicationMode(NewReplicationMode);
	}
	
}
