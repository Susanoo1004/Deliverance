// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

// Sets default values
ASaveManager::ASaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaveManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveManager::SyncBeforeSave_Implementation(FSaveData& OutData)
{
	/*ISaveEventHandler::SyncBeforeSave_Implementation(OutData);*/
}

void ASaveManager::SyncAfterLoad_Implementation(const FSaveData& InData)
{
	/*ISaveEventHandler::SyncAfterLoad_Implementation(InData);*/
}
