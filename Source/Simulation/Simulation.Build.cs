using UnrealBuildTool;

public class Simulation : ModuleRules
{
	public Simulation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "EchoesOfWarCore"
		});
	}
}
