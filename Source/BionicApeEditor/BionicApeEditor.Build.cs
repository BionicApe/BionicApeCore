// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BionicApeEditor : ModuleRules
{
	public BionicApeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "Source/Editor/Blutility/Private",
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"Blutility",
				"UMG",
				"UMGEditor",
				"EditorScriptingUtilities",
				"UnrealEd",
				"WorkspaceMenuStructure",
				"Slate",
				"SlateCore",
				"ApplicationCore",
				"Json",
				"EditorFramework",//Introduced in UE5
				"ImageWrapper"
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "JsonUtilities",
				"Json",
				"ToolMenus",
				"EditorStyle",
				"Projects",
				"GameProjectGeneration",//Used to refresh visual studio project
				"DesktopPlatform",
				"AppFramework",
				"EngineSettings",
				"PropertyEditor",//Can be deleted?
			}
			);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
