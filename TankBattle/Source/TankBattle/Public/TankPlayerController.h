// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "Tank.h" // replaced by forward declaration
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include


class ATank;

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	// virtual: my children can also inherit from me
	// override: I will inherit from my parent with same function but change logic.
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;


private: 
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OUTHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	float ReachLength = 1000000;

	bool LookDirection(FVector2D ScreenLocation, FVector& OUTLookDirection) const;
	bool GetVectorHitLocation(FVector OUTLookDirection, FVector& OUTHitLocation) const;
};
