// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ro3ots : ModuleRules
{
	public Ro3ots(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
