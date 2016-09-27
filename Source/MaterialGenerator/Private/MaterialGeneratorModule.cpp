#include "MaterialGeneratorModulePCH.h"
#include "MaterialGeneratorModule.h"
#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "BaseEditorToolCustomization.h"
#include "BaseEditorTool.h"
#include "MaterialTool.h"
#include "ContentBrowserModule.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Editor/MaterialEditor/Public/IMaterialEditor.h"
#include "Toolkits/ToolkitManager.h"

#undef WITH_EDITORONLY_DATA
#define WITH_EDITORONLY_DATA 1

IMPLEMENT_MODULE(MaterialGeneratorModule, NewMenu );

void MaterialGeneratorModule::StartupModule()
{
	CreateNewMenu();
}

void MaterialGeneratorModule::ShutdownModule()
{

}

void MaterialGeneratorModule::CreateNewMenu()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	PropertyModule.RegisterCustomClassLayout(TEXT("BaseEditorTool"), FOnGetDetailCustomizationInstance::CreateStatic(&FBaseEditorToolCustomization::MakeInstance));


	CommandList = MakeShareable(new FUICommandList);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>( "LevelEditor" );

	//MainMenuExtender = MakeShareable( new FExtender );
	//MainMenuExtender->AddMenuBarExtension( "Help",
	//									EExtensionHook::After,
	//									NULL,
	//									FMenuBarExtensionDelegate::CreateStatic( &MaterialGeneratorModule::OnCreateNewMenu ) );

	//LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MainMenuExtender);

	// Add in a button to create the material generation menu
	//TSharedRef<FExtender> MenuExtender(new FExtender());
	//MenuExtender->AddMenuExtension(
	//	TEXT("Help"),
	//	EExtensionHook::After,
	//	CommandList.ToSharedRef(),
	//	FMenuExtensionDelegate::CreateStatic(&MaterialGeneratorModule::createMaterialGeneratorToolMenu));

	//LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);


	MainMenuExtender = MakeShareable(new FExtender);
	MainMenuExtender->AddMenuBarExtension("Help",
		EExtensionHook::After,
		NULL,
		FMenuBarExtensionDelegate::CreateStatic(&MaterialGeneratorModule::createMaterialGeneratorToolMenu));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MainMenuExtender);
}

void MaterialGeneratorModule::OnCreateNewMenu( FMenuBarBuilder& InMenuBarBuilder )
{
	InMenuBarBuilder.AddPullDownMenu
	(
		LOCTEXT( "MaterialCreateEditor1", "Create new Material" ),
		LOCTEXT( "MaterialCreateEditorTooltip1", "Generate a new Kilograph material" ),
		FNewMenuDelegate::CreateStatic(&MaterialGeneratorModule::createMaterial)
	);
}

void MaterialGeneratorModule::createMaterial(FMenuBuilder& InMenuBarBuilder)
{
	
}

void MaterialGeneratorModule::createMaterialGeneratorToolMenu(FMenuBarBuilder& InMenuBarBuilder)
{
	InMenuBarBuilder.AddPullDownMenu
	(
		LOCTEXT("MaterialCreateEditor1", "Create new Material"),
		LOCTEXT("MaterialCreateEditorTooltip1", "Generate a new Kilograph material"),
		FNewMenuDelegate::CreateStatic(&MaterialGeneratorModule::createMaterialGeneratorToolMenuCallback)
	);
}

void MaterialGeneratorModule::createMaterialGeneratorToolMenuCallback(FMenuBuilder& InMenuBarBuilder)
{
	UE_LOG(LogTemp, Warning, TEXT("You've clicked my cool button!!!"));

	UBaseEditorTool* ToolInstance = NewObject<UBaseEditorTool>(GetTransientPackage(), UMaterialTool::StaticClass());
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);
	TSharedRef<SWindow> Window = PropertyModule.CreateFloatingDetailsView(ObjectsToView, /*bIsLockeable=*/ false);

	Window->SetOnWindowClosed(FOnWindowClosed::CreateStatic(&MaterialGeneratorModule::OnToolWindowClosed, ToolInstance));
}

void MaterialGeneratorModule::OnToolWindowClosed(const TSharedRef<SWindow>& Window, UBaseEditorTool* Instance)
{
	Instance->RemoveFromRoot();
}
