// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BatsToiSupreme_Real : ModuleRules
{
	public BatsToiSupreme_Real(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"ApplicationCore",
			"Core", 
			"CoreOnline",
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"MotionWarping",
			"GASCompanion",
			"EngineSettings",
			"GameplayAbilities",
			"GameLiftServerSDK",
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] {
			"CommonInput",
			"EnhancedInput",
			"GameplayTasks",
			"GameplayTags",
			"UMG",
			"CommonUI",
		});

		bEnableExceptions = true;

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
