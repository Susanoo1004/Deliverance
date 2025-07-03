// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SaveSystemSettings.generated.h"

USTRUCT(BlueprintType)
struct FSaveGameSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Name of the save file (.sav binary format)."))
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Index used to differentiate users on the same device. Keep it at zero unless deployed on console."))
	int32 UserIndex;

	FSaveGameSettings()
	{
		SaveSlotName = "Save";
		UserIndex = 0;
	}
};

/**
 *
 */
UCLASS(BlueprintType)
class DROWNEDPATH_API USaveSystemSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Tooltip = "Settings inherited by Unreal's USaveGame class."))
	FSaveGameSettings SaveGameSettings;
};
