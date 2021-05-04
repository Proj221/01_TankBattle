// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// auto Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f, Barrel Elevation Called at speed %f!"),Time, RelativeSpeed);

	// move the barrel the right amout this frame
	// given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;
	auto ClampedRotation = FMath::Clamp<float>(RawNewRotation, MinDegreesRotation, MaxDegreesRotation);
	UE_LOG(LogTemp, Warning, TEXT("TURRET IN ROTATION TO: %f!"), ClampedRotation);
	SetRelativeRotation(FRotator( 0, ClampedRotation, 0));
}