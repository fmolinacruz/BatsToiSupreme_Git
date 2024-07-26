// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BatsToiSupreme_RealServerTarget : TargetRules
{
	public BatsToiSupreme_RealServerTarget(TargetInfo Target) : base(Target)
	{
        Name = "BatsToiSupreme_RealServer";

        Type = TargetType.Server;
        // Update build settings
        DefaultBuildSettings = BuildSettingsVersion.Latest;

        // Update include order version
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange(new[] { "BatsToiSupreme_Real" });
	}
}
