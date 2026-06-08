// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Recolectaryentregar : ModuleRules
{
	public Recolectaryentregar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Recolectaryentregar",
			"Recolectaryentregar/Variant_Platforming",
			"Recolectaryentregar/Variant_Platforming/Animation",
			"Recolectaryentregar/Variant_Combat",
			"Recolectaryentregar/Variant_Combat/AI",
			"Recolectaryentregar/Variant_Combat/Animation",
			"Recolectaryentregar/Variant_Combat/Gameplay",
			"Recolectaryentregar/Variant_Combat/Interfaces",
			"Recolectaryentregar/Variant_Combat/UI",
			"Recolectaryentregar/Variant_SideScrolling",
			"Recolectaryentregar/Variant_SideScrolling/AI",
			"Recolectaryentregar/Variant_SideScrolling/Gameplay",
			"Recolectaryentregar/Variant_SideScrolling/Interfaces",
			"Recolectaryentregar/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
