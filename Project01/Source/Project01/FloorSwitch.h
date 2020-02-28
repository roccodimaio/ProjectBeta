// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class PROJECT01_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	/** Overlap volume for functionality to be triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorSwitch)
	class UBoxComponent* TriggerBox;

	/** Switch the character will step on */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorSwitch)
	class UStaticMeshComponent* FloorSwitch;

	/** Door that will move when floor switch is stepped on */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorSwitch)
	UStaticMeshComponent* Door; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorSwitch)
	class UParticleSystemComponent* DoorSteamLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorSwitch)
	class UParticleSystemComponent* DoorSteamRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
