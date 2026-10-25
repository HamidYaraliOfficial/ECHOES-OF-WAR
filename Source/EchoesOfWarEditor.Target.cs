using UnrealBuildTool;
using System.Collections.Generic;

public class EchoesOfWarEditorTarget : TargetRules
{
	public EchoesOfWarEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange(new string[] {
			"EchoesOfWarCore", "Simulation", "World", "Units", "Combat",
			"Logistics", "Economy", "Politics", "Research", "AI",
			"Save", "Networking", "UI", "Tools", "EchoesOfWar"
		});
	}
}
