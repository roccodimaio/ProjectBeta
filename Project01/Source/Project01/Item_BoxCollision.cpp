// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_BoxCollision.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values
AItem_BoxCollision::AItem_BoxCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionVolume"));
	RootComponent = BoxCollisionVolume; 

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticles"));
	IdleParticlesComponent->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AItem_BoxCollision::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem_BoxCollision::OnOverLapBegin);
	BoxCollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AItem_BoxCollision::OnOverLapEnd);
	
}

// Called every frame
void AItem_BoxCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem_BoxCollision::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OverLapBegin()"));
}

void AItem_BoxCollision::OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OverLapEnd()"));
}