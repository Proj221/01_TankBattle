// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Enum for aiming states
UENUM()
enum class EFiringStatus : uint8 {
	Locked,
	Aiming,
	Reloading,
	NoAmmo
};

// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector OUTHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetFire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = Setup)
	int GetLeftAmmo() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards();
	void MoveTurretTowards();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 20000; // sensible starting value, 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSecond = 3;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// UClass* ProjectileBlueprint; // Alternative...A
	TSubclassOf<AProjectile> ProjectileBlueprint; // Alternative...B

	bool IsBarrelMoving();

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int AmmoInTotal = 10;

	int AmmoLeft = 0;
	

};
