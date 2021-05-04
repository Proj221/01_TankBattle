// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	// auto Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f, Barrel Elevation Called at speed %f!"),Time, RelativeSpeed);

	// move the barrel the right amout this frame
	// given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);
	// UE_LOG(LogTemp, Warning, TEXT("BARREL IN ELEVATION TO: %f!"), ClampedElevation);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}