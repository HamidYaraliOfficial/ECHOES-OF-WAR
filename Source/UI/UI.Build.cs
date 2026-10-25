using UnrealBuildTool;

public class UI : ModuleRules
{
	public UI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "UMG", "Slate", "SlateCore",
			"Json", "JsonUtilities", "EchoesOfWarCore"
		});
	}
}
