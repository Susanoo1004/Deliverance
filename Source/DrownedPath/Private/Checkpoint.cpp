// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	// Root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	// Trigger Box and Visual
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(DefaultSceneRoot);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerBoxVisual"));
	TriggerBoxVisual->SetupAttachment(TriggerBox);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		TriggerBoxVisual->SetStaticMesh(CubeMesh.Object);
		TriggerBoxVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Respawn Dummy Arrow -> Dummy -> Name
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	ForwardArrow->SetupAttachment(DefaultSceneRoot);

	RespawnDummy = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RespawnDummy"));
	RespawnDummy->SetupAttachment(ForwardArrow);

	Name = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name"));
	Name->SetupAttachment(RespawnDummy);

	// Camera Forward -> Camera Arrow
	CameraShadow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraShadow"));
	CameraShadow->SetupAttachment(ForwardArrow);

	/*CameraShadow->SetRelativeLocation(CameraShadowSettings->FollowCameraPreset.PosOffset);
	CameraShadow->SetWorldRotation(CameraShadowSettings->FollowCameraPreset.RotationOffset);*/

	CameraForward = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraForward"));
	CameraForward->SetupAttachment(CameraShadow);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

void ACheckpoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (IsValid(CameraShadow)) {
		// Compute offset from rotation and arm length (like a spring arm)
		FVector Offset = CameraShadowRotation.Vector() * -100; // negative to go backwards
		FVector NewLocation = GetActorLocation() + Offset;

		CameraShadow->SetWorldLocation(NewLocation);
		CameraShadow->SetWorldRotation(CameraShadowRotation);
	}
}

void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (Cast<ATestThirdPerson5_4_4Character>(OtherActor)) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "OVERLAP");

		Cast<UMyGameInstance>(GetGameInstance())->SaveSystem->ASynchronousSaveGame();
	}*/
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
