// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;	//  should this tick??? NO

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FString OurTankName, FVector OUTHitLocation, float LaunchSpeed) {
	if (!Barrel) { 
		UE_LOG(LogTemp, Warning, TEXT("Barrel Is Missing!"));
		return; }
	if (!Turret) { 
		UE_LOG(LogTemp, Warning, TEXT("Turret Is Missing!"));
		return; }

	// auto BarrelLocation = Barrel->GetComponentLocation();
	// UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s from %s"), *OurTankName, *OUTHitLocation.ToString(), *BarrelLocation.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("%s is firing at %f"), *OurTankName, LaunchSpeed);

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
		auto AimDirection = OUTLaunchVelocity.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("Aim Solution Found!"), Time);
	}
	else {
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("No Aim Found!"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// work out the difference between current barrel rotation and aimDirection
	auto BarrelRotatator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotatator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotatator - BarrelRotatator;
	// UE_LOG(LogTemp, Warning, TEXT("BarrelAimAsRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch); // the pitch angle will be clamped in the tank barrel elevate.
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	// work out the difference between current barrel rotation and aimDirection
	auto TurretRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotatator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotatator - TurretRotator;

	// UE_LOG(LogTemp, Warning, TEXT("TurretAimAsRotator: %s"), *DeltaRotator.ToString());

	// here is to avoid the turret to rotate in the shortest way
	// avoid to yaw in the long way
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw); // the yaw angle will be clamped in the tank turret rotate.
	}
	
}