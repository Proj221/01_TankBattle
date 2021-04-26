// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	// call the default actions behind begin play
	Super::BeginPlay();


	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller not possessing a tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller begin play with %s"), *ControlledTank->GetName())
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller not possessing a tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller is aiming at %s"), *PlayerTank->GetName())
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}