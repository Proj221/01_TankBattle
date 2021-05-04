// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
// DONT forget to change this one on a SM component!!!
// Otherwise it is not possible to call from BP!!!
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;	//sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesRotation = 90;	//TODO set

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinDegreesRotation = -90;	//TODO set
	
};
