// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Remake : ModuleRules
{
	public Remake(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"GameplayTasks",
			"NavigationSystem",
			"InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});
		
		PublicIncludePaths.AddRange(new string[]
		{
			"Remake/Public/Component",
			"Remake/Public/Animation",
			"Remake/Public/DamageActor",
			"Remake/Public/Weapon",
			"Remake/Public/Actor",
			"Remake/Public/AI",
			"Remake/Public/Shop",
			"Remake/Public/FPG",
			"Remake/Public/InteractiveActor"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
