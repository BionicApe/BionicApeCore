// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BionicApeEditor : ModuleRules
{
    public BionicApeEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
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
				// ... add other public dependencies that you statically link with here ...
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Blutility",
                "UMG",
                "UMGEditor",
                "EditorScriptingUtilities",
                "UnrealEd",
            }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
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
