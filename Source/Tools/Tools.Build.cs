using UnrealBuildTool;

public class Tools : ModuleRules
{
	public Tools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "Json", "JsonUtilities",
			"EchoesOfWarCore", "World", "Simulation"
		});
		if (Target.Type == TargetType.Editor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "EditorStyle" });
		}
	}
}
