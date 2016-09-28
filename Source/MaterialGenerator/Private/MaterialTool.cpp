#include "MaterialGeneratorModulePCH.h"
#include "MaterialTool.h"
#include "../AssetTools/Public/AssetToolsModule.h"
#include "ScopedTransaction.h"
#include "ContentBrowserModule.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "AssetRegistryModule.h"

#define LOCTEXT_NAMESPACE "DemoTools"

UMaterialTool::UMaterialTool()
	: Super(FObjectInitializer::Get())
{
}

void UMaterialTool::GenerateMaterial()
{
	const FString DefaultSuffix = TEXT("_Inst");

	if (Texture1 == NULL || Texture2 == NULL || Texture3 == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Have to set texture parameters before a material can be generated!!"));
		return;
	}

	if (BaseMaterial == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Have to set a base material before you can generate a material instance!!"));
		return;
	}

	// Create an appropriate and unique name 
	FString Name;
	FString PackageName;
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	UE_LOG(LogTemp, Warning, TEXT("Base material outer name: %s"), *BaseMaterial->GetOutermost()->GetName());
	// If the material name hasn't been set just use the base material's name
	if (NewMaterialName == "")
	{
		AssetToolsModule.Get().CreateUniqueAssetName(BaseMaterial->GetOutermost()->GetName(), DefaultSuffix, PackageName, Name);
	}
	else
	{
		AssetToolsModule.Get().CreateUniqueAssetName(TEXT("/Game/") + NewMaterialName, TEXT(""), PackageName, Name);
	}

	UMaterialInstanceConstant* generatedInstance = Cast<UMaterialInstanceConstant>(AssetToolsModule.Get().CreateAsset(Name, FPackageName::GetLongPackagePath(PackageName),
		UMaterialInstanceConstant::StaticClass(), NULL));

	generatedInstance->SetParentEditorOnly((UMaterialInterface *) BaseMaterial);

	if (generatedInstance != NULL)
	{
		generatedInstance->SetTextureParameterValueEditorOnly(FName(TEXT("Texture1")), Texture1);
		generatedInstance->SetTextureParameterValueEditorOnly(FName(TEXT("Texture2")), Texture2);
		generatedInstance->SetTextureParameterValueEditorOnly(FName(TEXT("Texture3")), Texture3);
	}

	generatedInstance->MarkPackageDirty();

	FAssetRegistryModule::AssetCreated(generatedInstance);
}


#undef LOCTEXT_NAMESPACE