using UnrealBuildTool;

public class Politics : ModuleRules
{
	public Politics(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "EchoesOfWarCore"
		});
	}
}
