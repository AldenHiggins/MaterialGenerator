#pragma once

#include "BaseEditorTool.h"
#include "MaterialTool.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EBaseMaterialType : uint8
{
	Base_Mat 	UMETA(DisplayName = "Default"),
	Cloth_Mat 	UMETA(DisplayName = "Cloth"),
	Metal_Mat	UMETA(DisplayName = "Metal")
};

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
	EBaseMaterialType BaseMaterialType;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UMaterial *BaseMaterial;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Diffuse;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Normal;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UTexture2D *Specular;

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool IsMetallic;


	UFUNCTION(Exec)
	void GenerateMaterial();
};
