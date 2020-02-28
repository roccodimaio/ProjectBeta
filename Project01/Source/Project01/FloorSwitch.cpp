// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox; 
	
	// Specify type of collision for this Actor (QueryOnly - Overlap events only)
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// ObjectType assigned to the trigger box
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	
	// Set the response to all collision object types.  Set all to ignore and specify required below
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// Set Collision to pawn and respond with an overlap event
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Set inital size of TriggerBox
	TriggerBox->SetBoxExtent(FVector(62.0f, 62.0f, 32.0f));

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	DoorSteamLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DoorSteamLeft"));
	DoorSteamLeft->SetupAttachment(GetRootComponent());

	DoorSteamRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DoorSteamRight"));
	DoorSteamRight->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd);
	
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin")); 
}

void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
}

