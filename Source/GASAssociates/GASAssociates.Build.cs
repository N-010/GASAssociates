// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASAssociates : ModuleRules
{
	public GASAssociates(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		var publicPath = ModuleDirectory + "/Public";
		var privatePath = ModuleDirectory + "/Private";
		
		PublicIncludePaths.AddRange(
			new[]
			{
				publicPath
			}
		);


		PrivateIncludePaths.AddRange(
			new[]
			{
				privatePath
			}
		);


		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"GameplayAbilities", 
				"GameplayTags", 
				"GameplayTasks"
			}
		);
	}
}