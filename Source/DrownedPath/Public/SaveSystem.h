// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "SaveSystemSettings.h"

#include "SaveSystem.generated.h"

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ToolTip = "Transform of checkpont's player shadow."))
	FTransform SavedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ToolTip = "Name of the checkpoint."))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ToolTip = "Rotation of checkpoint's shadow camera"))
	FRotator CameraRotation;

	FSaveData()
	{
		CameraRotation = FRotator();
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreSaveEvent, FSaveData&, SaveData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostSaveEvent, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreLoadEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostLoadEvent, const FSaveData&, LoadedData);

/**
 *
 */
UCLASS()
class DROWNEDPATH_API USaveSystem : public USaveGame
{
	GENERATED_BODY()

	////////////////////////////////////////////////// VARIABLES //////////////////////////////////////////////////

	////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable)
	bool IsSaveInProgress();

	UFUNCTION(BlueprintCallable)
	bool IsLoadInProgress();

	UFUNCTION()
	void HandlePreSave();

	UFUNCTION()
	void HandlePostSave(const FString& SlotName, const int32 UserIndex, const bool bSuccess);

	UFUNCTION()
	void HandlePreLoad();

	UFUNCTION()
	void HandlePostLoad(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGame);

public:

	////////////////////////////////////////////////// VARIABLES //////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Structure containing every settings of this USaveGame subclass instance."))
	FSaveGameSettings SaveGameSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USaveSystemSettings* SaveSystemSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Structure containing every saved properties."))
	FSaveData SavedData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "Total number of save request."))
	int32 TotalSaveRequest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "Number of succeeded save request."))
	int32 SucceededSaveRequest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "Number of failed save request."))
	int32 FailedSaveRequest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "Total number of load request."))
	int32 TotalLoadRequest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "Number of succeeded load request."))
	int32 SucceededLoadRequest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "Number of failed load request."))
	int32 FailedLoadRequest;

	////////////////////////////////////////////////// EVENTS //////////////////////////////////////////////////

	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (ToolTip = "Called before saving to push data to the SaveSystem and trigger assigned events."))
	FOnPreSaveEvent OnPreSave;

	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (ToolTip = "Called after save to trigger assigned events."))
	FOnPostSaveEvent OnPostSave;

	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (ToolTip = "Called before loading to push data to the SaveSystem and trigger assigned events."))
	FOnPreLoadEvent OnPreLoad;

	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (ToolTip = "Called after load to trigger assigned events."))
	FOnPostLoadEvent OnPostLoad;

	////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Add delegates that copies data to the SaveSystem to OnPreSave & OnPostLoad events."))
	void RegisterSaveEventCallback(const TScriptInterface<ISaveEventHandler> SaveEventHandler);

	////////////////////////////////////////////// SAVE //////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Synchronous save operation. Pauses the game thread during execution."))
	bool SynchronousSaveGame();

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Asynchronous save operation. Executing on another thread."))
	bool ASynchronousSaveGame();

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Binary save operation. Pauses the game thread during execution."))
	bool BinarySaveGame();

	////////////////////////////////////////////// LOAD //////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Synchronous load operation. Pauses the game thread during execution."))
	bool SynchronousLoadGame();

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Asynchronous load operation. Executing on another thread."))
	bool ASynchronousLoadGame();

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Binary load operation. Pauses the game thread during execution."))
	bool BinaryLoadGame();
};
