using UnrealBuildTool;

public class EchoesOfWar : ModuleRules
{
	public EchoesOfWar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"UMG", "Json", "JsonUtilities",
			"EchoesOfWarCore", "Simulation", "World", "Units", "Combat",
			"Logistics", "Economy", "Politics", "Research", "AI",
			"Save", "Networking", "UI"
		});
	}
}
