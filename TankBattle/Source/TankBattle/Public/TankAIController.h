// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()


private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	// virtual: my children can also inherit from me
	// override: I will inherit from my parent with same function but change logic.
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};
