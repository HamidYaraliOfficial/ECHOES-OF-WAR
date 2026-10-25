using UnrealBuildTool;

public class Logistics : ModuleRules
{
	public Logistics(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "NavigationSystem", "EchoesOfWarCore", "Simulation"
		});
	}
}
