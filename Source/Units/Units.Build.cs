using UnrealBuildTool;

public class Units : ModuleRules
{
	public Units(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "EchoesOfWarCore"
		});
	}
}
