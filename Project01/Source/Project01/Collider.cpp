// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyColliderMovementComponent.h" 
#include "GameFramework/Controller.h"

// Sets default values
ACollider::ACollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
	
	// Set radius of the SphereComponent
	SphereComponent->InitSphereRadius(40.0f);

	// Set collision of the SphereComponent
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -20.0f));

	// Code to hardcode a static mesh to MeshComponent.
	//.. static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/ParagonMinions/FX/Meshes/PlayerBuffs/SM_Buff_Tetra.SM_Buff_Tetra'"));
	
	//if(MeshComponentAsset.Succeeded())
	//{
	//		MeshComponent->SetStaticMesh(MeshComponentAsset.Object)
	//}

	// Create SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	// Attached SpringArmComonent to the Scene Root
	SpringArmComponent->SetupAttachment(GetRootComponent());

	// Setup SprintArmComponent rotation (tilt up/down)
	SpringArmComponent->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);

	// Setup SpringArmComponent lenght (camera distance from Pawn)
	SpringArmComponent->TargetArmLength = 400.0f;

	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 3.0f;

	// Create CameraComponent 
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	
	// Attached CameraComponent to the end of the SpringArmCompnent (Camera behind Pawn)
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UMyColliderMovementComponent>(TEXT("MovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent; 

	CameraInput = FVector2D(0.0f, 0.0f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();

	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	FRotator NewSpringArmRotation = SpringArmComponent->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, -80.0f, -15.0f);

	SpringArmComponent->SetWorldRotation(NewSpringArmRotation);
}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::YawCamera);
}

UPawnMovementComponent* ACollider::GetMovementComponent() const
{
	return OurMovementComponent;
}

// Will move Collider Forward/Backward on AxisInput
void ACollider::MoveForward(float Value)
{
	FVector Forward = GetActorForwardVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Value * Forward);
	}
	
}

// Will move Collider Right/Left on AxisInput
void ACollider::MoveRight(float Value)
{
	FVector Right = GetActorRightVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Value * Right);
	}
	
}
void ACollider::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}
void ACollider::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}



