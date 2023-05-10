// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SpatialInventory : ModuleRules
{
	public SpatialInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput"});
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] { "SpatialInventory/Public/" });
		PrivateIncludePaths.AddRange(new string[] { "SpatialInventory/Private/" });
	}
}
