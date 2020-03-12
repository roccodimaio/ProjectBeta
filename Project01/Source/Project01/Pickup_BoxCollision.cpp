// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_BoxCollision.h"

APickup_BoxCollision::APickup_BoxCollision()
{

}

void APickup_BoxCollision::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverLapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT("Pickup_BoxCollision::OverLapBegin()"));
}

void APickup_BoxCollision::OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverLapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	UE_LOG(LogTemp, Warning, TEXT("Pickup_BoxCollision::In OverLapEnd()"));

}
