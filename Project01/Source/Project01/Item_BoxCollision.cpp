// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_BoxCollision.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"


// Sets default values
AItem_BoxCollision::AItem_BoxCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionVolume"));
	RootComponent = BoxCollisionVolume; 

	OverlapVolume = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapVolume"));
	OverlapVolume->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	OutsideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutsideMesh"));
	OutsideMesh->SetupAttachment(GetRootComponent());

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticles"));
	IdleParticlesComponent->SetupAttachment(GetRootComponent());
	
	bRotate = false; 

	RotationRate = 45.0f;
}

// Called when the game starts or when spawned
void AItem_BoxCollision::BeginPlay()
{
	Super::BeginPlay();

	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem_BoxCollision::OnOverLapBegin);
	OverlapVolume->OnComponentEndOverlap.AddDynamic(this, &AItem_BoxCollision::OnOverLapEnd);
	
}

// Called every frame
void AItem_BoxCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator Rotation = GetActorRotation();

		// increase rotation by rotational rate
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}

}

void AItem_BoxCollision::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OverLapBegin()"));

	// Spawn OverlapParticleSystem
	if (OverlapParticles)
	{
		// Call SpawnEmitterAtLoction function (#include Kismet/GameplayStatics and Engine/World
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.0f), true);
	}
	if (OverlapSound)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
	}
	Destroy();
}

void AItem_BoxCollision::OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OverLapEnd()"));
}