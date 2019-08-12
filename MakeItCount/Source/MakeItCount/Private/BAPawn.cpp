// Fill out your copyright notice in the Description page of Project Settings.


#include "BAPawn.h"
#include "Components/SphereComponent.h"

// Sets default values
ABAPawn::ABAPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABAPawn::BeginPlay()
{
	Super::BeginPlay();
	
	InitialYaw = GetActorRotation().Yaw;
	HalfMaxRotation = MaxRotationAngle * 0.5f;
}

// Called every frame
void ABAPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABAPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ABAPawn::Rotate(float RotationDirection)
{
	RotationDirection = FMath::Clamp<float>(RotationDirection, -1, 1);
	auto RotationChange = RotationDirection * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = GetActorRotation();
	Rotation.Yaw += RotationChange;
	Rotation.Yaw = FMath::Clamp<float>(Rotation.Yaw, (InitialYaw - HalfMaxRotation), (InitialYaw + HalfMaxRotation));

	SetActorRelativeRotation(Rotation);
}

