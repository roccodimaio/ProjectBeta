// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimeInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainAnimeInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	bLeap = false; 

	JumpLeapLimit = 300.0f; 
}

void UMainAnimeInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		// Get speed of Pawn
		FVector Speed = Pawn->GetVelocity();

		// Check if Pawn is on the ground
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);

		// Update movement speed, magnitude of MovementSpeed vector
		MovementSpeed = LateralSpeed.Size();

		//UE_LOG(LogTemp, Warning, TEXT("MovementSpeed %f"), MovementSpeed);

		bIsInAir = Pawn->GetMovementComponent()->IsFalling(); 

		if (MovementSpeed >= JumpLeapLimit)
		{
			bLeap = true; 
		}
		else
		{
			bLeap = false; 
		}

	}
}
