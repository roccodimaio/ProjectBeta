// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initalize default RootComponent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a default UStaticMeshComponent and assign it to MeshComponent
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// Attached MeshComponent to the RootComponent
	MeshComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f));
	Camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurrentVelocity = FVector(0.0f);

	MaxSpeed = 100.0f; 

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AEnemyBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AEnemyBase::MoveRight);

}

void AEnemyBase::MoveForward(float Value)
{
	// Clamp Value between -1 and 1 then multiply by max speed then assign to CurrentVelocity in Y direction
	CurrentVelocity.X = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed; 
}

void AEnemyBase::MoveRight(float Value)
{
	// Clamp Value between -1 and 1 then multiply by max speed then assign to CurrentVelocity in X direction
	CurrentVelocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;
}

