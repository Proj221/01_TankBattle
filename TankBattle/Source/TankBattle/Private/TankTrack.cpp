// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack(){
	PrimaryComponentTick.bCanEverTick = true;	//  should this tick??? NO
}


// Called every frame
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// apply sideway forces
	// calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work out the required acceleration at this frame
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// calculate and apply side force for (F = M*a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = CorrectionAcceleration * (TankRoot->GetMass()) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float throttle) {
	auto Name = GetName();

	auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle: %s"), *Name, *ForceApplied.ToString());
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}