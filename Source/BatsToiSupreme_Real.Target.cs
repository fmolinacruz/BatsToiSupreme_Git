// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BatsToiSupreme_RealTarget : TargetRules
{
	public BatsToiSupreme_RealTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        // Update build settings
        DefaultBuildSettings = BuildSettingsVersion.Latest;

        // Update include order version
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("BatsToiSupreme_Real");

		bUseUnityBuild = true;
	}
}
