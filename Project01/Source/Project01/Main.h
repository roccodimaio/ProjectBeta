// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA (DisplayName = "Normal"),
	ESS_BelowMinimum UMETA (DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA (DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA (DisplayName = "ExhaustedRecovering"),
	ESS_MAX UMETA (DisplayName = "DefaultMAX")
};

UCLASS()
class PROJECT01_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	// Array that stores FVectors
	TArray<FVector> PickupLocations;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	/** Set movement status and running speed */
	void SetMovementStatus(EMovementStatus Status);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	bool bSprintKeyDown;

	/** Pressed down to enable sprinting */
	void SprintKeyDown();

	/** Released to stop sprinting */
	void SprintkeyUp(); 

	/** Camera boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom; 

	/** Camera that follows the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera; 

	/**  The base rate at which to turn the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** The base rate at which to tilt the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/**
	/*
	/* Player Stats
	/*
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	float MaxStamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Mana;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	float MaxMana; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	float ManaRegenRate; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 Aether; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxAether; 

	void DecrementHealth(float Amount);

	void Die();

	void IncrementAether(int32 Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Call via input to turn at a given rate
	* @param Rate This is a normalized rate, ie 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Call via input to look up/down at a given rate
	* @param Rate This is a normalized rate, ie 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	bool bActionButtonDown;
	bool bWeaponEquipped;
	bool bWeaponAttached;

	void ActionButtonDown();
	void ActionButtonUp();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	

	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AWeapon* AttachedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverlappingItem;

	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToSet) { EquippedWeapon = WeaponToSet; }
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetAttachedWeapon(AWeapon* WeaponToAttach) { AttachedWeapon = WeaponToAttach; }
	FORCEINLINE AWeapon* GetAttachedWeapon() { return AttachedWeapon; }

	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

};