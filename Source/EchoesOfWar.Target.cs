using UnrealBuildTool;
using System.Collections.Generic;

public class EchoesOfWarTarget : TargetRules
{
	public EchoesOfWarTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange(new string[] {
			"EchoesOfWarCore", "Simulation", "World", "Units", "Combat",
			"Logistics", "Economy", "Politics", "Research", "AI",
			"Save", "Networking", "UI", "EchoesOfWar"
		});
	}
}
