#pragma once

#include "BaseEditorTool.h"
#include "MaterialTool.generated.h"

UCLASS(Blueprintable)
class UMaterialTool : public UBaseEditorTool
{
	GENERATED_BODY()

public:
	UMaterialTool();

public:
	UPROPERTY(EditAnywhere, Category = "Settings")
	FString NewMaterialName;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UMaterial *BaseMaterial;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Texture1;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Texture2;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Texture3;

	UFUNCTION(Exec)
	void GenerateMaterial();
};
