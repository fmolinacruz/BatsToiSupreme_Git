// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BatsToiSupreme_RealEditorTarget : TargetRules
{
	public BatsToiSupreme_RealEditorTarget(TargetInfo Target) : base(Target)
	{
        Name = "BatsToiSupreme_RealEditor";

        Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
        // Update include order version
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange(new[] { "BatsToiSupreme_Real", "BatsToiSupreme_RealEditor" });
	}
}
