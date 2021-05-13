// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// change the tank tick to FALSE, remove the tick method in .h
	PrimaryActorTick.bCanEverTick = false;

	// no need to add protection to pointers as added at constructor
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
	// TankMovementComponent is removed to a composite of the tank_bp, if this is not commented, the tankmovementcompoenet is considered like tankaimingcomponent, as a subobject
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s HUAWEI: TANK CPP CONSTRUCT"), *TankName);

}

void ATank::BeginPlay() {
	// DO NEED THIS!!!
	Super::BeginPlay();
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s HUAWEI: TANK CPP BEGINPLAY"), *TankName);
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


void ATank::AimAt(FVector OUTHitLocation) {
	// auto OurTankName = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s"), *OurTankName, *OUTHitLocation.ToString());

	// change the print out to aiming component
	// protect the pointer!!!!
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(GetName(), OUTHitLocation, LaunchSpeed);
}


void ATank::SetFire() {
	// UE_LOG(LogTemp, Warning, TEXT("FIRING!"));

	// this is the fire rate calculator
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond;
	

	if (Barrel && isReloaded) { 
		// spawn a projectile if there is a barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}

}



