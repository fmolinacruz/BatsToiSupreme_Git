// Copyright 2022 The Reallusion Authors. All Rights Reserved.

using UnrealBuildTool;

public class RLLiveLink : ModuleRules
{
    public RLLiveLink(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Networking",
                "Sockets",
                "Json",
                "JsonUtilities",
                "LiveLinkInterface",
                "Engine"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Projects",
                "InputCore",
                "UnrealEd",
                "LevelEditor",
                "ContentBrowser",
                "DesktopPlatform",
                "ImageWrapper",
                "EditorStyle",
                "RawMesh",
                "BlueprintGraph",
                "ApplicationCore",
                "CinematicCamera",
                "FBX",
                "LevelSequence",
                "MovieScene",
                "LevelSequenceEditor",
                "Sequencer",
                "MovieSceneTracks",
                "MovieSceneTools",
                "UMG",
                "CinematicCamera",
                "MovieSceneTracks"
            }
            );
        PublicDefinitions.AddRange(
            new string[]
            {
                "_WIN32_WINNT_WIN10_TH2",
                "_WIN32_WINNT_WIN10_RS1",
                "_WIN32_WINNT_WIN10_RS2",
                "_WIN32_WINNT_WIN10_RS3",
                "_WIN32_WINNT_WIN10_RS4",
                "_WIN32_WINNT_WIN10_RS5",
            }
            );
    }
}
