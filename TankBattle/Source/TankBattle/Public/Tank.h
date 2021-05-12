// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "TankAimingComponent.h" // replaced by forward delcaration
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel; // Forward Declaration
class UTankTurret;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector OUTHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetFire();

protected:
	// Called when the game starts or when spawned
	// virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000; // sensible starting value, 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// UClass* ProjectileBlueprint; // Alternative...A
	TSubclassOf<AProjectile> ProjectileBlueprint; // Alternative...B

	// this is a loca var to indicate tank barrel, besides this, there is a setter to tankAimingComponent for passing a global barrel var
	// local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	// set fire rate
	float ReloadTimeInSecond = 3;

	double LastFireTime = 0;
};
