// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BAAimingComponent.generated.h"

class UBA_ArcDrawerComponent;
class ABAProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAKEITCOUNT_API UBAAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBAAimingComponent();

private:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UBA_ArcDrawerComponent* ArcDrawerToSet, UStaticMeshComponent* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void ActivateChargingShot();
	
private:
	UBA_ArcDrawerComponent* ArcDrawer = nullptr;

	UStaticMeshComponent* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float MinLaunchSpeed = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float MaxLaunchSpeed = 150;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ChargingSpeed = 2;

	float LaunchSpeed;

	void ChargeShot(float chargeSpeed);

	bool bCharging = false;

	int Shots = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ABAProjectile> ProjectileBlueprint;
};
