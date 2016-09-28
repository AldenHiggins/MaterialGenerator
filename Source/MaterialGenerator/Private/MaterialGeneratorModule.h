#pragma once

#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "MaterialGenerator"

class MaterialGeneratorModule : public IModuleInterface
{

private:

	TSharedPtr<FExtender> MainMenuExtender;

public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void CreateNewMenu();

	TSharedPtr<FUICommandList> CommandList;

	static void createMaterialGeneratorToolMenu(FMenuBarBuilder& InMenuBarBuilder);

	static void createMaterialGeneratorToolMenuCallback(FMenuBuilder& InMenuBarBuilder);

	static void OnToolWindowClosed(const TSharedRef<SWindow>& Window, UBaseEditorTool* Instance);
};