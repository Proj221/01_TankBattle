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
	void Elevate(float DegreePerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;	//sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesElevation = 40;	//TODO set

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinDegreesElevation = 0;	//TODO set
	
};
