// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BatsToiSupreme_RealServerTarget : TargetRules
{
	public BatsToiSupreme_RealServerTarget(TargetInfo Target) : base(Target)
	{
        Name = "BatsToiSupreme_RealServer";

        Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "BatsToiSupreme_Real" });
	}
}
