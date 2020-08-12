// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CerealDemo : ModuleRules
{
	public CerealDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		PublicIncludePaths.AddRange(new string[]
		{
			"C:/Users/Brian_2/Documents/Dev/dev_library/cereal-1.3.0/include",
			"C:/Users/Brian_2/Documents/Dev/dev_library/MSVC/BRMUtils"
		});
		bUseRTTI = true;
		bEnableExceptions = true;
	}
}
