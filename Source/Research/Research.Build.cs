using UnrealBuildTool;

public class Research : ModuleRules
{
	public Research(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "EchoesOfWarCore"
		});
	}
}
