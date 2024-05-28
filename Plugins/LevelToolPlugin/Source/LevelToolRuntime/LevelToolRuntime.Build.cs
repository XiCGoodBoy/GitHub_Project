using System.IO;
using UnrealBuildTool;

public class LevelToolRuntime : ModuleRules
{
    public LevelToolRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "NavigationSystem",
                "GameplayDebugger",
                "UMG",
                "Projects",
                "DeveloperSettings",
                "LevelToolCommon",
            }
        );
        
        //拷贝Image插件的Image文件下的内容到包中
        // ReSharper disable once InconsistentNaming
        var Image_Directory_Path = Path.Combine(ModuleDirectory, "../../Image/*.*");
        RuntimeDependencies.Add(Image_Directory_Path);
    }
}