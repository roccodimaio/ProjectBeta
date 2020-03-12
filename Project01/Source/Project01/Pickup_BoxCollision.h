// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_BoxCollision.h"
#include "Pickup_BoxCollision.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT01_API APickup_BoxCollision : public AItem_BoxCollision
{
	GENERATED_BODY()

public:
	APickup_BoxCollision(); 

	virtual void OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
