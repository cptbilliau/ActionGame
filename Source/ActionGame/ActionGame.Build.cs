// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionGame : ModuleRules
{
	public ActionGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem", "AIModule", "Niagara", "UMG", "NetCore"});
		PrivateDependencyModuleNames.AddRange(new string[]{"CommonUI", "CommonUIEditor"});
	}
}
