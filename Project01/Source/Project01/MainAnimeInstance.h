// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimeInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT01_API UMainAnimeInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	
	virtual void NativeInitializeAnimation() override;

	// Function to update the animation data every frame
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;

	// Speed at which to use leaping animation or standard jump animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float JumpLeapLimit;

	// TODO add is acceleratings to determine jump animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bLeap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;


};
