// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyColliderMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT01_API UMyColliderMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
