// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

void ATankPlayerController::BeginPlay() {

	// call the default actions behind begin play
	Super::BeginPlay();


	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing a tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller begin play with %s"), *ControlledTank->GetName())
	}
	
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector OUTHitLocation;

	if (GetSightRayHitLocation(OUTHitLocation)) { // has side-effect, is going to line trace
		// tell controlled tank to aim at this point
		GetControlledTank()->AimAt(OUTHitLocation);
	}	
}

// get world location is linetrace thru crosshair, return true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OUTHitLocation) const{
	// find the crosshair position in pixel coordinates
	int32 OUTViewportSizeX, OUTViewportSizeY;
	GetViewportSize(OUTViewportSizeX, OUTViewportSizeY);
	FVector2D ScreenLocation = FVector2D(OUTViewportSizeX * CrossHairXLocation, OUTViewportSizeY * CrossHairYLocation);
	// "de-project" the screen position of the crosshair to a world direction
	FVector OUTLookDirection;
	if (LookDirection(ScreenLocation, OUTLookDirection)) {
		// line trace that look direction, and see what we hit (up to max range)
		GetVectorHitLocation(OUTLookDirection, OUTHitLocation);
	}
	
	return true;
}

bool ATankPlayerController::LookDirection(FVector2D ScreenLocation, FVector& OUTLookDirection) const {
	FVector OUTCameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUTCameraWorldLocation, OUTLookDirection); 
}

bool ATankPlayerController::GetVectorHitLocation(FVector OUTLookDirection, FVector& OUTHitLocation) const {
	FHitResult OUTHitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + OUTLookDirection * ReachLength;
	// if you want to use linetracesinglebychannel(), you always first getworld()
	if (GetWorld()->LineTraceSingleByChannel(OUTHitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		OUTHitLocation = OUTHitResult.Location;
		// it is fun to draw a debug line here
		DrawDebugLine(GetWorld(), StartLocation, OUTHitLocation, FColor(255, 0, 0), false, -1.0f, 1.0f, 20.0f);
		return true;
	}
	OUTHitLocation = FVector(0);
	return false;
}
