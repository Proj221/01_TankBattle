// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UTankAimingComponent::AimAt(FString OurTankName, FVector OUTHitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }

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
		ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OUTLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// work out the difference between current barrel rotation and aimDirection
	auto BarrelRotatator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotatator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotatator - BarrelRotatator;
	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(5); //TODO remove magic number

}