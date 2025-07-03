// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ArrowComponent.h"

#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PrimitiveComponent.h"
#include "FollowCameraSettings.h"

#include "Checkpoint.generated.h"

UCLASS()
class DROWNEDPATH_API ACheckpoint : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root", meta = (AllowPrivateAccess))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger", meta = (AllowPrivateAccess))
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger", meta = (AllowPrivateAccess))
	UStaticMeshComponent* TriggerBoxVisual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Respawn", meta = (AllowPrivateAccess))
	UArrowComponent* ForwardArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Respawn", meta = (AllowPrivateAccess))
	USkeletalMeshComponent* RespawnDummy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Respawn", meta = (AllowPrivateAccess))
	UTextRenderComponent* Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess))
	UStaticMeshComponent* CameraShadow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess))
	UArrowComponent* CameraForward;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", Category = "Attributes", meta=(ClampMin="0.3", ClampMax="1.0", UIMin="0.3", UIMax="1.0"))
	float Opacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", Category = "Attributes", meta=(ClampMin="-360.0", ClampMax="360.0", UIMin="-360.0", UIMax="360.0"))
	FRotator CameraShadowRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	UFollowCameraSettings* CameraShadowSettings;

	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
