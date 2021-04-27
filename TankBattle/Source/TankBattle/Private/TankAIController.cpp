// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

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

void ATankAIController::Tick(float DeltaTime) {
	// every tick the AI tank is looking for the player tank
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	// draw the debug line
	DrawDebugLine(GetWorld(), GetControlledTank()->GetActorLocation(), GetPlayerTank()->GetActorLocation(), FColor(255, 0, 0), false, -1.0f, 1.0f, 20.0f);
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}