using UnrealBuildTool;

public class Networking : ModuleRules
{
	public Networking(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "NetCore", "EchoesOfWarCore"
		});
	}
}
