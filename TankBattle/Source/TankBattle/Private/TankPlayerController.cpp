// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>


void ATankPlayerController::BeginPlay() {

	// call the default actions behind begin play
	Super::BeginPlay();


	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller cannot find a playing component at play"));
	}
		
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscrive our local method to the tank's death event
		PossessedTank->OnTankDied.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerTankDeath);
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
	if (GetControlledTank()) {
		FVector OUTHitLocation;
		bool bGotHitLocation = GetSightRayHitLocation(OUTHitLocation);
		// UE_LOG(LogTemp, Warning, TEXT("bGotHitLocaiton: %i"), bGotHitLocation)
		if (bGotHitLocation) { // has side-effect, is going to line trace
			// tell controlled tank to aim at this point
			GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(OUTHitLocation);
		}
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
		return GetVectorHitLocation(OUTLookDirection, OUTHitLocation);
	}
	
	return false;
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
		// DrawDebugLine(GetWorld(), StartLocation, OUTHitLocation, FColor(255, 0, 0), false, -1.0f, 1.0f, 20.0f);
		return true;
	}
	OUTHitLocation = FVector(0);
	return false;
}

void ATankPlayerController::OnPlayerTankDeath() {
	auto GetPlayerTank = GetPawn();
	if (GetPlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("PLAYER: %s DIED!!!"), *GetPawn()->GetName());
		StartSpectatingOnly();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("YOU ARE SPECULATING THE TANK WORLD"));
	}
	
	
}