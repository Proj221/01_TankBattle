// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

void ATankAIController::BeginPlay() {

	// call the default actions behind begin play
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscrive our local method to the tank's death event
		PossessedTank->OnTankDied.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto ControlledTank = (GetPawn());
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank && ControlledTank) {
		// Move to player
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		// every tick the AI tank is looking for the player tank
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// draw the debug line
		// DrawDebugLine(GetWorld(), GetControlledTank()->GetActorLocation(), GetPlayerTank()->GetActorLocation(), FColor(255, 0, 0), false, -1.0f, 1.0f, 20.0f);

		// only fire if they are locked
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
			AimingComponent->SetFire();
		}
	}

}

void ATankAIController::OnTankDeath() {
	auto GetAITank = GetPawn();
	if (GetAITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI_TANK: %s DIED!!!"), *GetPawn()->GetName());
		GetAITank->DetachFromControllerPendingDestroy();
	}
}