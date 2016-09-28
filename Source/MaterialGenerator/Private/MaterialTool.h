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
	UTexture2D *Diffuse;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Normal;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Specular;

	UFUNCTION(Exec)
	void GenerateMaterial();
};
