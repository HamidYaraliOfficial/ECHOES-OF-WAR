using UnrealBuildTool;

public class AI : ModuleRules
{
	public AI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "AIModule",
			"EchoesOfWarCore", "Simulation", "Units", "Logistics", "Economy"
		});
	}
}
