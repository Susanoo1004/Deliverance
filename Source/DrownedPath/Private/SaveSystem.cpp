// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem.h"

#include "SaveEventHandler.h"

#include "Kismet/GameplayStatics.h"

bool USaveSystem::IsSaveInProgress()
{
	return (SucceededSaveRequest + FailedSaveRequest) != TotalSaveRequest;
}

bool USaveSystem::IsLoadInProgress()
{
	return (SucceededLoadRequest + FailedLoadRequest) != TotalLoadRequest;
}

void USaveSystem::HandlePreSave()
{
	TotalSaveRequest++;
	OnPreSave.Broadcast(SavedData);
}

void USaveSystem::HandlePostSave(const FString& SlotName, const int32 UserIndex, const bool bSuccess)
{
	(bSuccess) ? SucceededSaveRequest++ : FailedSaveRequest++;

	if (bSuccess) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Save Succeeded..."));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Save Failed..."));
	}

	OnPostSave.Broadcast(bSuccess);
}

void USaveSystem::HandlePreLoad()
{
	TotalLoadRequest++;
	OnPreLoad.Broadcast();
}

void USaveSystem::HandlePostLoad(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGame)
{
	IsValid(LoadedGame) ? SucceededLoadRequest++ : FailedLoadRequest++;

	if (IsValid(LoadedGame)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Load Succeeded..."));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, SavedData.SavedLocation.ToString());
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Load Failed..."));
	}

	OnPostLoad.Broadcast(SavedData);
}

void USaveSystem::RegisterSaveEventCallback(const TScriptInterface<ISaveEventHandler> SaveEventHandler)
{
	if (!SaveEventHandler.GetObject()) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Interface is NULL"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Interface is not NULL"));
	}

	if (!SaveEventHandler) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("NULL"));
		return;
	}

	OnPreSave.AddUniqueDynamic(SaveEventHandler.GetInterface(), &ISaveEventHandler::SyncBeforeSave);
	OnPostLoad.AddUniqueDynamic(SaveEventHandler.GetInterface(), &ISaveEventHandler::SyncAfterLoad);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("Successfully added delegates"));
}

bool USaveSystem::SynchronousSaveGame()
{
	HandlePreSave();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Magenta, SavedData.SavedLocation.ToString());

	if (UGameplayStatics::SaveGameToSlot(this, SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex)) {
		HandlePostSave(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, true);
		return true;
	}

	return false;
}

bool USaveSystem::ASynchronousSaveGame()
{
	HandlePreSave();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Saving Data..."));
	FAsyncSaveGameToSlotDelegate SavedDelegate;
	// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
	SavedDelegate.BindUObject(this, &USaveSystem::HandlePostSave);

	// Start async save process.
	UGameplayStatics::AsyncSaveGameToSlot(this, SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, SavedDelegate);

	return false;
}

bool USaveSystem::BinarySaveGame()
{
	HandlePreSave();

	TArray<uint8> OutSaveData;
	if (UGameplayStatics::SaveGameToMemory(this, OutSaveData)) {
		// The operation succeeded, and OutSaveData now contains a binary represenation of the SaveGame object.
		if (UGameplayStatics::SaveDataToSlot(OutSaveData, SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex)) {
			// The operation succeeded, and InSaveData has been written to the save file defined by the slot name and user ID we provided.
			HandlePostSave(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, true);
			return true;
		}
	}
	return false;
}

bool USaveSystem::SynchronousLoadGame()
{
	HandlePreLoad();

	// Load the save game
	if (USaveGame* BaseLoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex)) {
		if (USaveSystem* LoadedGame = Cast<USaveSystem>(BaseLoadedGame)) {
			SavedData = LoadedGame->SavedData;
			HandlePostLoad(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, LoadedGame);
			return true;
		}
	}

	HandlePostLoad(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, this);
	return false;
}

bool USaveSystem::ASynchronousLoadGame()
{
	HandlePreLoad();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, TEXT("Loading Data..."));

	// Set up the delegate.
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	LoadedDelegate.BindUObject(this, &USaveSystem::HandlePostLoad);
	UGameplayStatics::AsyncLoadGameFromSlot(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, LoadedDelegate);

	return false;
}

bool USaveSystem::BinaryLoadGame()
{
	HandlePreLoad();

	TArray<uint8> OutSaveData;
	if (UGameplayStatics::LoadDataFromSlot(OutSaveData, SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex)) {
		// The operation succeeded, and OutSaveData now contains a binary represenation of the SaveGame object.
		if (USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::LoadGameFromMemory(OutSaveData))) {
			SavedData = SaveGameInstance->SavedData;
			// The operation succeeded, and SaveGameInstance was able to cast to type we expected (UMySaveGame).
			HandlePostLoad(SaveGameSettings.SaveSlotName, SaveGameSettings.UserIndex, this);
			return true;
		}
	}
	return false;
}
