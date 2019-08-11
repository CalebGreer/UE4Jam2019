using UnrealBuildTool;
using System.Collections.Generic;

public class MakeItCountTarget : TargetRules
{
	public MakeItCountTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "MakeItCount" } );
	}
}
