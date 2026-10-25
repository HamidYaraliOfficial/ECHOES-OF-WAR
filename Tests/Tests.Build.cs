using UnrealBuildTool;

public class Tests : ModuleRules
{
	public Tests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "EchoesOfWarCore", "Simulation",
			"Logistics", "AI", "Save", "Units", "Combat"
		});
	}
}
