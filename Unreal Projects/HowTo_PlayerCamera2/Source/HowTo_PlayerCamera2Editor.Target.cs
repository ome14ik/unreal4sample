// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowTo_PlayerCamera2EditorTarget : TargetRules
{
	public HowTo_PlayerCamera2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "HowTo_PlayerCamera2" } );
	}
}
