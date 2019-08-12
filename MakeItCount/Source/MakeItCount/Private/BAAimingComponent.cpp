// Fill out your copyright notice in the Description page of Project Settings.


#include "BAAimingComponent.h"
#include "BA_ArcDrawerComponent.h"
#include "BAProjectile.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UBAAimingComponent::UBAAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	LaunchSpeed = MinLaunchSpeed;
}


// Called when the game starts
void UBAAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBAAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bCharging)
	{
		ChargeShot(ChargingSpeed);
	}
}

void UBAAimingComponent::Initialize(UBA_ArcDrawerComponent * ArcDrawerToSet, UStaticMeshComponent* BarrelToSet)
{
	ArcDrawer = ArcDrawerToSet;
	ArcDrawer->ChangeVelocity(MinLaunchSpeed);

	Barrel = BarrelToSet;
	Barrel->SetVisibility(false);
}

void UBAAimingComponent::Fire()
{
	bCharging = false;
	if (!ensure(ProjectileBlueprint)) { return; }
	if (!ensure(Barrel)) { return; }

	UE_LOG(LogTemp, Warning, TEXT("LaunchSpeed: %f"), LaunchSpeed);

	auto Projectile = GetWorld()->SpawnActor<ABAProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);

	Shots--;

	LaunchSpeed = MinLaunchSpeed;
	ArcDrawer->ChangeVelocity(LaunchSpeed);
}

void UBAAimingComponent::ActivateChargingShot()
{
	if (Shots <= 0) { return; }
	bCharging = true;
}

void UBAAimingComponent::ChargeShot(float chargeSpeed)
{
	LaunchSpeed += chargeSpeed;
	LaunchSpeed = FMath::Clamp<float>(LaunchSpeed, MinLaunchSpeed, MaxLaunchSpeed);

	ArcDrawer->ChangeVelocity(LaunchSpeed);
}
