using UnrealBuildTool;

public class LevelToolEditor : ModuleRules
{
    public LevelToolEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "SlateCore",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "InputCore",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EditorFramework",
                "UnrealEd",
                "ToolMenus",
                "Projects",
                "LevelToolRuntime", 
                "LevelToolCommon",
            }
        );
    }
}