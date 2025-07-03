// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SaveEventHandler.h"

#include "SaveManager.generated.h"

UCLASS()
class DROWNEDPATH_API ASaveManager : public AActor, public ISaveEventHandler
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SyncBeforeSave_Implementation(FSaveData& OutData) override;
    void SyncAfterLoad_Implementation(const FSaveData& InData) override;
};
