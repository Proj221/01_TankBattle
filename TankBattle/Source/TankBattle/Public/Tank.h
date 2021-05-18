// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();

	FTankDelegate OnTankDied;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 StartingHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 CurrentHealth = 100;

};
