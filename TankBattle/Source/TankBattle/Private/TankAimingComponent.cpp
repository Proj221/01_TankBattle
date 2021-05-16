// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	//  should this tick??? NO

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// so that the first fire is after a initial reload
	LastFireTime = FPlatformTime::Seconds();

	// set letammo to total ammo
	AmmoLeft = AmmoInTotal;
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (AmmoLeft <= 0) {
		FiringStatus = EFiringStatus::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecond) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const {
	return FiringStatus;
}

int UTankAimingComponent::GetLeftAmmo() const
{
	return AmmoLeft;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OUTHitLocation) {
	if (!ensure(Barrel)) { 
		UE_LOG(LogTemp, Warning, TEXT("Barrel Is Missing!"));
		return; }
	if (!ensure(Turret)) { 
		UE_LOG(LogTemp, Warning, TEXT("Turret Is Missing!"));
		return; }

	FVector OUTLaunchVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUTLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		OUTHitLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace); // comment this line to produce BUG! However, if we have this line, we found that even the barrel is pointing to the sky, the aim still counts!
	
	if (bHaveAimSolution)
	{
		AimDirection = OUTLaunchVelocity.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString());
		// MoveBarrelTowards();
		MoveTurretTowards();
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("Aim Solution Found!"), Time);
	}
	else {
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("No Aim Found!"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards() {
	// work out the difference between current barrel rotation and aimDirection
	auto BarrelRotatator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotatator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotatator - BarrelRotatator;
	// UE_LOG(LogTemp, Warning, TEXT("BarrelAimAsRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch); // the pitch angle will be clamped in the tank barrel elevate.
}

void UTankAimingComponent::MoveTurretTowards() {

	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("Barrel Is Missing!"));
		return;
	}
	if (!ensure(Turret)) {
		UE_LOG(LogTemp, Warning, TEXT("Turret Is Missing!"));
		return;
	}

	// work out the difference between current barrel rotation and aimDirection
	auto TurretRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotatator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotatator - TurretRotator;

	// UE_LOG(LogTemp, Warning, TEXT("TurretAimAsRotator: %s"), *DeltaRotator.ToString());


	Barrel->Elevate(DeltaRotator.Pitch); // the pitch angle will be clamped in the tank barrel elevate.
	// here is to avoid the turret to rotate in the shortest way
	// avoid to yaw in the long way
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw); // the yaw angle will be clamped in the tank turret rotate.
	}
	
}

void UTankAimingComponent::SetFire() {
	// UE_LOG(LogTemp, Warning, TEXT("FIRING!"));

	if (Barrel && FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::NoAmmo) {
		// spawn a projectile if there is a barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoLeft -= 1;
	}

}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	return !BarrelForwardVector.Equals(AimDirection, 0.1);

}

