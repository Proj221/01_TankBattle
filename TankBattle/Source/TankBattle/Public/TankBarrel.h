// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is the max down speed while +1 is the max up speed 
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10;	//sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesElevation = 60;	//TODO set

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinDegreesElevation = 0;	//TODO set
	
};
