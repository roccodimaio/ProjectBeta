// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		// Set HUDOverlay
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	// Add the HUDOverlay to the view port
	HUDOverlay->AddToViewport(); 

	// Set the HUDOverlay to visible
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

}
