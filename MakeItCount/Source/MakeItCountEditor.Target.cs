using UnrealBuildTool;
using System.Collections.Generic;

public class MakeItCountEditorTarget : TargetRules
{
	public MakeItCountEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "MakeItCount" } );
	}
}
