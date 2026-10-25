using UnrealBuildTool;

public class EchoesOfWarCore : ModuleRules
{
	public EchoesOfWarCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "Json", "JsonUtilities"
		});
	}
}
