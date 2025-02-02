#include "StalkerMainMenu.h"
#include "Kernel/Unreal/GameSettings/StalkerGameSettings.h"
#include "Framework/Commands/Commands.h"
#include "../StalkerEditorStyle.h"
#include "../../StalkerEditorManager.h"
#include "../Commands/StalkerEditorCommands.h"

void StalkerMainMenu::Initialize()
{
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		auto LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension("Help", EExtensionHook::After, GStalkerEditorManager->UICommandList, FMenuBarExtensionDelegate::CreateRaw(this, &StalkerMainMenu::MakePulldownMenu));
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}
}

void StalkerMainMenu::Destroy()
{

}

void StalkerMainMenu::MakePulldownMenu(FMenuBarBuilder& InMenuBuilder)
{
	InMenuBuilder.AddPullDownMenu(
		FText::FromString("Stalker"),
		FText::FromString("Open the Stalker menu"),
		FNewMenuDelegate::CreateRaw(this, &StalkerMainMenu::FillPulldownMenu),
		"Stalker"
	);
}

void StalkerMainMenu::FillPulldownMenu(FMenuBuilder& InMenuBuilder)
{
	InMenuBuilder.BeginSection(NAME_None, FText::FromString("Games"));
	{
		FUIAction Action(
			FExecuteAction::CreateLambda([]()
				{
					UStalkerGameSettings* SGSettings = GetMutableDefault<UStalkerGameSettings>();
					if (SGSettings->EditorStartupGame != EStalkerGame::COP)
					{
						SGSettings->EditorStartupGame = EStalkerGame::COP;
						SGSettings->TryUpdateDefaultConfigFile();
						SGSettings->ReInitilizeXRay();
					}
				}
			),
			FCanExecuteAction(),
			FIsActionChecked::CreateLambda([]()
				{
					const UStalkerGameSettings* SGSettings = GetDefault<UStalkerGameSettings>();
					return SGSettings->EditorStartupGame == EStalkerGame::COP;
				}
			)
					);
		InMenuBuilder.AddMenuEntry(FText::FromString("Call of Pripyat"), FText::GetEmpty(), FSlateIcon(FStalkerEditorStyle::GetStyleSetName(), "StalkerEditor.COP"), Action, NAME_None, EUserInterfaceActionType::RadioButton);
	}
	{
		FUIAction Action(
			FExecuteAction::CreateLambda([]()
				{
					UStalkerGameSettings* SGSettings = GetMutableDefault<UStalkerGameSettings>();
					if (SGSettings->EditorStartupGame != EStalkerGame::CS)
					{
						SGSettings->EditorStartupGame = EStalkerGame::CS;
						SGSettings->TryUpdateDefaultConfigFile();
						SGSettings->ReInitilizeXRay();
					}
				}
			),
			FCanExecuteAction(),
					FIsActionChecked::CreateLambda([]()
						{
							const UStalkerGameSettings* SGSettings = GetDefault<UStalkerGameSettings>();
							return SGSettings->EditorStartupGame == EStalkerGame::CS;
						}
					)
					);
		InMenuBuilder.AddMenuEntry(FText::FromString("Clear Sky"), FText::GetEmpty(), FSlateIcon(FStalkerEditorStyle::GetStyleSetName(), "StalkerEditor.CS"), Action, NAME_None, EUserInterfaceActionType::RadioButton);
	}
	{
		FUIAction Action(
			FExecuteAction::CreateLambda([]()
				{
					UStalkerGameSettings* SGSettings = GetMutableDefault<UStalkerGameSettings>();
					if (SGSettings->EditorStartupGame != EStalkerGame::SHOC)
					{
						SGSettings->EditorStartupGame = EStalkerGame::SHOC;
						SGSettings->TryUpdateDefaultConfigFile();
						SGSettings->ReInitilizeXRay();
					}
				}
			),
			FCanExecuteAction(),
					FIsActionChecked::CreateLambda([]()
						{
							const UStalkerGameSettings* SGSettings = GetDefault<UStalkerGameSettings>();
							return SGSettings->EditorStartupGame == EStalkerGame::SHOC;
						}
					)
					);
		InMenuBuilder.AddMenuEntry(FText::FromString("Shadow of Chernobyl"), FText::GetEmpty(), FSlateIcon(FStalkerEditorStyle::GetStyleSetName(), "StalkerEditor.SOC"), Action, NAME_None, EUserInterfaceActionType::RadioButton);
	}

	InMenuBuilder.EndSection();

	InMenuBuilder.BeginSection(NAME_None, FText::FromString("Tools"));
	{
		InMenuBuilder.AddMenuEntry(StalkerEditorCommands::Get().ImportUITextures, "ImportUITextures", FText::FromString("Import UI Textures"));
		InMenuBuilder.AddMenuEntry(StalkerEditorCommands::Get().ImportPhysicalMaterials, "ImportPhysicalMaterials", FText::FromString("Import Physical Materials"));
		InMenuBuilder.AddMenuEntry(StalkerEditorCommands::Get().ImportMeshes, "ImportMeshes", FText::FromString("Import Meshes"));
	}

	InMenuBuilder.EndSection();

	InMenuBuilder.BeginSection(NAME_None, FText::FromString("Build"));
	{
		InMenuBuilder.AddMenuEntry(
			StalkerEditorCommands::Get().BuildCForm,
			"BuildCForm",
			FText::FromString("Build CForm"),
			FText::GetEmpty(),
			FSlateIcon(FStalkerEditorStyle::GetStyleSetName(), "StalkerEditor.BuildCForm")
		);

		InMenuBuilder.AddMenuEntry(
			StalkerEditorCommands::Get().BuildAIMap,
			"BuildAIMap",
			FText::FromString("Build AIMap"),
			FText::GetEmpty(),
			FSlateIcon(FStalkerEditorStyle::GetStyleSetName(),	"StalkerEditor.BuildAIMap")
		);

		InMenuBuilder.AddMenuEntry(
			StalkerEditorCommands::Get().BuildLevelSpawn,
			"BuildLevelSpawn",
			FText::FromString("Build LevelSpawn"),
			FText::GetEmpty(),
			FSlateIcon(FStalkerEditorStyle::GetStyleSetName(), "StalkerEditor.BuildLevelSpawn")
		);

		InMenuBuilder.AddMenuEntry(
			StalkerEditorCommands::Get().BuildGameSpawn,
			"BuildGameSpawn",
			FText::FromString("Build GameSpawn"),
			FText::GetEmpty(),
			FSlateIcon(FStalkerEditorStyle::GetStyleSetName(), "StalkerEditor.BuildGameSpawn")
		);
	}

	InMenuBuilder.EndSection();
}