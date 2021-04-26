// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

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

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

