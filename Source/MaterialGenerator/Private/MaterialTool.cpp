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

	if (Diffuse == NULL || Normal == NULL || Specular == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Have to set texture parameters before a material can be generated!!"));
		return;
	}

	if (BaseMaterial == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Have to set a base material before you can generate a material instance!!"));
		BaseMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("/Game/16068StdrWalk/Materials/Main_MATERIALS/Base_Master.Base_Master")));
		if (BaseMaterial == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("Couldn't load default base material!!!"));
			return;
		}
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
		// Set the Diffuse texture
		FStaticParameterSet updatedParams;
		generatedInstance->GetStaticParameterValues(updatedParams);
		for (int paramIdx = 0; paramIdx < updatedParams.StaticSwitchParameters.Num(); paramIdx++)
		{
			if (updatedParams.StaticSwitchParameters[paramIdx].ParameterName == FName("Enable Diffuse Map"))
			{
				// Flip the boolean to what we need and override it...
				updatedParams.StaticSwitchParameters[paramIdx].Value = true;
				updatedParams.StaticSwitchParameters[paramIdx].bOverride = true;
			}
			else if (updatedParams.StaticSwitchParameters[paramIdx].ParameterName == FName("Enable Specular Map"))
			{
				// Flip the boolean to what we need and override it...
				updatedParams.StaticSwitchParameters[paramIdx].Value = true;
				updatedParams.StaticSwitchParameters[paramIdx].bOverride = true;
			}
		}

		// this does absolutely nothing, even though it should!
		((UMaterialInstance *) generatedInstance)->UpdateStaticPermutation(updatedParams);

		generatedInstance->SetTextureParameterValueEditorOnly(FName(TEXT("Map #1")), Diffuse);
		generatedInstance->SetTextureParameterValueEditorOnly(FName(TEXT("Normal")), Normal);
		generatedInstance->SetTextureParameterValueEditorOnly(FName(TEXT("Map Specular")), Specular);
	}

	generatedInstance->MarkPackageDirty();

	FAssetRegistryModule::AssetCreated(generatedInstance);
}


#undef LOCTEXT_NAMESPACE