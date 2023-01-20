// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BatsToiSupreme_Real : ModuleRules
{
	public BatsToiSupreme_Real(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
