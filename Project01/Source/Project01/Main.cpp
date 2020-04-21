// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera boom (pulls towards the player if there's a collision)
	CameraBoom = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	
	CameraBoom->SetupAttachment(GetRootComponent()); // Attaches the CameraBoom to the Root Component
	CameraBoom->TargetArmLength = 600.0f; // Distance camera is from player
	CameraBoom->bUsePawnControlRotation = true; // Allow spring arm to rotation from controller

	// Set size of collision capsule
	GetCapsuleComponent()->SetCapsuleSize(30.5f, 95.0f);

	// Create Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); 
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attaches the FollowCamera to the CameraBoom at the socket called SocketName
	FollowCamera->bUsePawnControlRotation = false; // Do not allow camera to follow along with rotation from controller

	// Set our turn rates for input
	BaseTurnRate = 65.0f;
	BaseLookUpRate = 65.0f; 

	// Do not rotate this Character when the controller rotates
	// Let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false; 

	// Access the CharacterMovementComponent

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // The speed (540) at which the character turns in the Yaw direction
	GetCharacterMovement()->JumpZVelocity = 650.0f; 
	GetCharacterMovement()->AirControl = 0.2f; 

	MaxHealth = 100.0f;
	Health = 60.0f; 
	MaxStamina = 150.0f;
	Stamina = 120.0f;
	MaxMana = 100.0f;
	ManaRegenRate = 10.0f;
	Mana = 80.0f;
	Aether = 0;
	MaxAether = 999999;

	RunningSpeed = 650.0f;
	SprintingSpeed = 950.0f; 

	bSprintKeyDown = false; 

	// Initialize ENUMS
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;

	StaminaDrainRate = 25.0f;
	StaminaRegenRate = 5.0f; 
	MinSprintStamina = 50.0f;
}



// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DeltaStamina = StaminaDrainRate * DeltaTime; 
	float DeltaRegenStamina = StaminaRegenRate * DeltaTime; 

	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if (bSprintKeyDown) // Sprint key pressed
		{
			if (Stamina - DeltaStamina <= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				Stamina -= DeltaStamina;
			}
			else
			{
				Stamina -= DeltaStamina; 
			}
			SetMovementStatus(EMovementStatus::EMS_Sprinting);
	
		}
		else // Sprint key up
		{
			if (Stamina + DeltaStamina >= MaxStamina)
			{
				Stamina = MaxStamina;
			}
			else
			{
				Stamina += DeltaRegenStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		if (bSprintKeyDown)
		{
			if (Stamina - DeltaStamina <= 0.0f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else
			{
				Stamina -= DeltaStamina;
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
		}
		else // Sprint key up
		{
			if (Stamina + DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaRegenStamina;
			}
			else
			{
				Stamina += DeltaRegenStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_Exhausted:
		if (bSprintKeyDown)
		{
			Stamina = 0.0f;
		}
		else // Sprint key up
		{
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			Stamina += DeltaRegenStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);

		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		if (Stamina + DeltaRegenStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaRegenStamina;
		}
		else
		{
			Stamina += DeltaRegenStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);

		break;
	default:
		break;
	}

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// check that PlayerInputCompnent is valid, if not stop code
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); // Bind key/button assigned to Jump to built in function from Character called Jump
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMain::SprintKeyDown); // Bind key/button assigned to SprintKeyDown function below
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMain::SprintkeyUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);  // Bind key/button assigned to MoveForward to the function MoveForward from &AMain
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);  // Bind key/button assigned to MoveRightto the function MoveRight from &AMain
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // Bind key/button assigned to Turn to built in function from Pawn called AddControllerYawInput
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput); // Bind key/button assigned to LookUp to built in look up function from Pawn called AddControllerPitchInput

	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate); // Bind key/button assigned to TurnRate to the function TurnAtRate from &AMain
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpAtRate); // Bind key/button assigned to LookUpRate to the function LookUpAtRate from &AMain


}

void AMain::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//  Foun out which way is forward

		// Find current rotation of the controller and assign to Rotation
		const FRotator Rotation = Controller->GetControlRotation();
		
		// Find current Yaw of the controller and assign to YawRotation
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Create FRotationMatrix from the current controller Yaw and get the unit axis to acess the X direction (Forward/Backward)
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Adding movement input for the character in the forward direction
		AddMovementInput(Direction, Value);
	}
}

void AMain::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//  Foun out which way is Right/Left

		// Find current rotation of the controller and assign to Rotation
		const FRotator Rotation = Controller->GetControlRotation();

		// Find current Yaw of the controller and assign to YawRotation
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Create FRotationMatrix from the current controller Yaw and get the unit axis to acess the Y direction (Right/Left)
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Adding movement input for the character in the Right/Left direction
		AddMovementInput(Direction, Value);
	}
}

void AMain::TurnAtRate(float Rate)
{	
	// Take input of Rate (0 or 1), multiple by BaseTurnRate, multiply by DeltaSeconds and rotate the controller on the Yaw for that frame
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpAtRate(float Rate)
{
	// Take input of Rate (0 or 1), multiple by BaseLookUpRate, multiply by DeltaSeconds and rotate the controller on the Pitch for that frame
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AMain::DecrementHealth(float Amount)
{
	if (Health - Amount <= 0.0f)
	{
		Health = 0.0f;
		Die();
	}
	else
	{
		Health -= Amount; 
	}
}

void AMain::Die()
{

}

void AMain::IncrementAether(int32 Amount)
{
	if (Aether + Amount >= MaxAether)
	{
		Aether = MaxAether;
	}
	else
	{
		Aether += Amount; 
	}
}


void AMain::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status; 
	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMain::SprintKeyDown()
{
	bSprintKeyDown = true; 
}

void AMain::SprintkeyUp()
{
	bSprintKeyDown = false; 
}

void AMain::ShowPickupLocations()
{
	for (int32 i = 0; i < PickupLocations.Num(); i++)
	{
		// Draw debug sphere at a location with 12 sections in green for 10 seconds with a thickness of 0.5
		UKismetSystemLibrary::DrawDebugSphere(this, PickupLocations[i] + FVector(0, 0, 75.0f), 25.0f, 12, FLinearColor::Green, 10.0f, 0.5f);
	}
}