// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

// DOES NOT WORK!!!
/*
void UTankMovementComponent::IntendMove(float Throw) { // NOT WORK!!!

	//throw		- 1					0					1
	//lateral
	//	- 1		S + D, L - R +		D, L0, R0			W + D, L + , R -
	//	0		S, L - , R -		NULL, L0, R0		W, L + , R +
	//	1		S + A, L + , R -	A, L0, R0			W + A, L - , R +

	if (!LeftTrack || !RightTrack) { return; }
	
	if (Throw) {	// if throw = 0, never move positively
		// UE_LOG(LogTemp, Warning, TEXT("MOVE LONGITUDINAL with Throw: %f"), Throw);
		if (Lateral) {
			LeftTrack->SetThrottle(-Throw * Lateral);
			RightTrack->SetThrottle(Throw * Lateral);
		}
		else {
			LeftTrack->SetThrottle(Throw);
			RightTrack->SetThrottle(Throw);
		}
		
	}

}
*/

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// no need to call super as it is replacing the logic here

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	// auto TankName = GetOwner()->GetName();
	// UE_LOG(LogTemp, Warning, TEXT("Tank: %s is moving at Velocity: %s"), *TankName, *AIForwardIntention.ToString());

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto ThrowProd = FVector::DotProduct(AIForwardIntention, TankForward);
	auto LateralCross = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	// UE_LOG(LogTemp, Warning, TEXT("Tank ThrowProd: %f, LateralCross: %f"), ThrowProd, LateralCross);

	IntendMoveForward(ThrowProd);
	IntendTurnRight(LateralCross);

}