#pragma once

#include "CoreMinimal.h"
#include "FollowCameraSettings.generated.h"

USTRUCT(BlueprintType)
struct FFollowCameraPreset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Position Offset of the camera. Value entered in the viewport window."))
	FVector PosOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Rotation Offset of the camera. Value entered in the viewport window."))
	FRotator RotationOffset;

	FFollowCameraPreset()
	{
		PosOffset = FVector();
		RotationOffset = FRotator();
	}
};

/**
 *
 */
UCLASS(BlueprintType)
class DROWNEDPATH_API UFollowCameraSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Tooltip = "Settings inherited by Unreal's USaveGame class."))
	FFollowCameraPreset FollowCameraPreset;
};
