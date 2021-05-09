// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// change the tank tick to FALSE, remove the tick method in .h
	PrimaryActorTick.bCanEverTick = false;

	// no need to add protection to pointers as added at constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

/*
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector OUTHitLocation) {
	// auto OurTankName = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s"), *OurTankName, *OUTHitLocation.ToString());

	// change the print out to aiming component
	TankAimingComponent->AimAt(GetName(), OUTHitLocation, LaunchSpeed);
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::SetFire() {
	UE_LOG(LogTemp, Warning, TEXT("FIRING!"));
}



