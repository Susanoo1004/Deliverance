// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveSystem.h"

#include "UObject/Interface.h"
#include "SaveEventHandler.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USaveEventHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class DROWNEDPATH_API ISaveEventHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SyncBeforeSave(FSaveData& OutData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SyncAfterLoad(const FSaveData& InData);
};
