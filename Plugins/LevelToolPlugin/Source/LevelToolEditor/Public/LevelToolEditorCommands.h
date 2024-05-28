// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

#define LOCTEXT_NAMESPACE "FLevelToolEditorCommands"

class FLevelToolEditorCommands final : public TCommands<FLevelToolEditorCommands>
{
public:

	FLevelToolEditorCommands()
		: TCommands<FLevelToolEditorCommands>(
			TEXT("LevelToolEditorCommands"),
			NSLOCTEXT("Contexts", "LevelToolEditorCommands", "Level Tool Editor"),
			NAME_None, FAppStyle::GetAppStyleSetName())
	{
	}
	//定义一个命令
	TSharedPtr< FUICommandInfo> LevelToolEditorCommonInfo;

	//通过使用UI Command将定义的FUICommandInfo命令注册,在之后将绑定行为到FUICommandInfo
	//UI_COMMAND( CommandId, FriendlyName, InDescription, CommandType, InDefaultChord, ... )
	virtual void RegisterCommands() override
	{
		UI_COMMAND(
			LevelToolEditorCommonInfo,
			"关卡缩放",
			"围绕场景原点来对场景进行一个缩放",
			EUserInterfaceActionType::Button,
			FInputChord());
	}
};

#undef LOCTEXT_NAMESPACE