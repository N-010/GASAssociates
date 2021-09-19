// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GameplayEffectTypesSubsystem.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"


float UGameplayEffectTypesSubsystem::GetDuration(const FGameplayEffectSpec& Spec)
{
	return Spec.GetDuration();
}

void UGameplayEffectTypesSubsystem::GetAllGrantedTags(const FGameplayEffectSpec& Spec, FGameplayTagContainer& Container)
{
	Spec.GetAllGrantedTags(Container);
}

void UGameplayEffectTypesSubsystem::GetAllAssetTags(const FGameplayEffectSpec& Spec, FGameplayTagContainer& Container)
{
	Spec.GetAllAssetTags(Container);
}

DEFINE_FUNCTION(UGameplayEffectTypesSubsystem::execGetGameplayEffectDefForSpec)
{
	P_GET_STRUCT_REF(FGameplayEffectSpec, Z_Param_Out_Spec);
	P_FINISH;
	P_NATIVE_BEGIN;
		*static_cast<const UGameplayEffect**>(RESULT_PARAM) = UGameplayEffectTypesSubsystem::GetGameplayEffectDefForSpec(
			Z_Param_Out_Spec);
	P_NATIVE_END;
}

const UGameplayEffect* UGameplayEffectTypesSubsystem::GetGameplayEffectDefForSpec(const FGameplayEffectSpec& Spec)
{
	return Spec.Def;
}

FGameplayEffectSpec UGameplayEffectTypesSubsystem::GetGameplayEffectSpecFromActiveGameplayEffectHandle(
	const FActiveGameplayEffectHandle& Handle)
{
	const UAbilitySystemComponent* AbilitySystemComponent = Handle.IsValid() ? Handle.GetOwningAbilitySystemComponent() : nullptr;
	if (IsValid(AbilitySystemComponent))
	{
		if (const FActiveGameplayEffect* ActiveGameplayEffect = AbilitySystemComponent->GetActiveGameplayEffect(Handle))
		{
			return ActiveGameplayEffect->Spec;
		}
	}

	return FGameplayEffectSpec();
}

DEFINE_FUNCTION(UGameplayEffectTypesSubsystem::execGetAbilitySystemComponentFromHandle)
{
	P_GET_STRUCT_REF(FActiveGameplayEffectHandle, Z_Param_Out_Handle);
	P_FINISH;
	P_NATIVE_BEGIN;
		*static_cast<const UAbilitySystemComponent**>(RESULT_PARAM) =
			UGameplayEffectTypesSubsystem::GetAbilitySystemComponentFromHandle(Z_Param_Out_Handle);
	P_NATIVE_END;
}

const UAbilitySystemComponent* UGameplayEffectTypesSubsystem::GetAbilitySystemComponentFromHandle(
	const FActiveGameplayEffectHandle& Handle)
{
	return Handle.IsValid() ? Handle.GetOwningAbilitySystemComponent() : nullptr;
}


bool UGameplayEffectTypesSubsystem::EqualEqual_ActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& A, const FActiveGameplayEffectHandle& B)
{
	return A == B;
}

bool UGameplayEffectTypesSubsystem::IsValid_ActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& A)
{
	return A.IsValid();
}
