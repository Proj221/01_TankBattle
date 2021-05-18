// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	
	int32 DamagePoints = FPlatformMath::TruncToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("%s CurrentHealth:%i/100"), *GetName(), CurrentHealth);
	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("TANK: %s DIED!!!"), *GetName());
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() {
	return (float)CurrentHealth / (float)StartingHealth;
}






