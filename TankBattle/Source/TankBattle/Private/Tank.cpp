// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// change the tank tick to FALSE, remove the tick method in .h
	PrimaryActorTick.bCanEverTick = false;

	// no need to add protection to pointers as added at constructor
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s HUAWEI: TANK CPP CONSTRUCT"), *TankName);

}

void ATank::BeginPlay() {
	// DO NEED THIS!!!
	Super::BeginPlay();
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s HUAWEI: TANK CPP BEGINPLAY"), *TankName);
}

/*
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/



