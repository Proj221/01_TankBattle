// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) {
	auto Name = GetName();

	auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle: %s"), *Name, *ForceApplied.ToString());
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}