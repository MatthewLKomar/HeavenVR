// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HeavenVR2 : ModuleRules
{
	public HeavenVR2(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
        PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "GameplayTasks", "UMG" });
    }
}
