// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMove(float Throw, float Lateral) {

	//throw		- 1					0					1
	//lateral
	//	- 1		S + D, L - R +		D, L0, R0			W + D, L + , R -
	//	0		S, L - , R -		NULL, L0, R0		W, L + , R +
	//	1		S + A, L + , R -	A, L0, R0			W + A, L - , R +

	
	if (Throw) {	// if throw = 0, never move positively
		UE_LOG(LogTemp, Warning, TEXT("MOVE LONGITUDINAL with Throw: %f"), Throw);
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