// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_BoxCollision.h"
#include "Main.h"

APickup_BoxCollision::APickup_BoxCollision()
{
	AetherCount = 1;
}

void APickup_BoxCollision::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverLapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT("Pickup_BoxCollision::OverLapBegin()"));

	// Check the other actor(s) that overlap
	if (OtherActor)
	{
		// Check if OtherActor is of class Main and assign to the variable Main, if not assign NULL to the variable Main
		AMain* Main = Cast<AMain>(OtherActor);

		// OtherActor is of class Main
		if (Main)
		{
			// Call function from Main to increment Aether
			Main->IncrementAether(AetherCount);
		}
	}
}

void APickup_BoxCollision::OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverLapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	UE_LOG(LogTemp, Warning, TEXT("Pickup_BoxCollision::In OverLapEnd()"));

}
