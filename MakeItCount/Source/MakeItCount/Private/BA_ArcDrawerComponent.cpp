// Fill out your copyright notice in the Description page of Project Settings.


#include "BA_ArcDrawerComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "BA_ball.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UBA_ArcDrawerComponent::UBA_ArcDrawerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxTimeInterval = 0.5f;
	TimeStep = 0.1f;

	//reserve a block of memory
	BallArray.Reserve(5);

}


//calculates the x displacement
float UBA_ArcDrawerComponent::CalculateDisplacementX(const float &initialVelocity, const float &time, const float &angle)
{
	return initialVelocity * time * FMath::Cos(angle);
}

//calculate the Y displacement(Z in unreal)
float UBA_ArcDrawerComponent::CalculateDisplacementY(const float & initialVelocityY, const float & time, const float & gravity, const float &angle)
{
	return (initialVelocityY * time * FMath::Sin(angle)) + ((0.5 * gravity) * (time * time));
}

// Called when the game starts
void UBA_ArcDrawerComponent::BeginPlay()
{
	Super::BeginPlay();

	//initial set up 
	MyOwner = this->GetOwner();
	UWorld* World = MyOwner->GetWorld();
	Gravity = World->GetGravityZ();

	FString OwnerName = MyOwner->GetName();
	UE_LOG(LogClass, Warning, TEXT("This a testing statement. %s"), *OwnerName);

	if (ensure(BallToSpawn)) 
	{
		//spawn the points and add them to the array
		for (int i = 0; i < 5; i++)
		{
			ABA_ball* spawnedBall = (ABA_ball*)World->SpawnActor<ABA_ball>(BallToSpawn);

			//attach it to the owner so they turn with us
			spawnedBall->AttachToActor(MyOwner, FAttachmentTransformRules::KeepRelativeTransform);

			BallArray.Add(spawnedBall);
		}
	}

}


// Called every frame
void UBA_ArcDrawerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	DrawArc(initVelocity);
}

void UBA_ArcDrawerComponent::DrawArc(const FVector initVelocity)
{
	if (!ensure(BallToSpawn)) { return; }

	int i = 0;
	for (float t = 0; t < MaxTimeInterval; t += TimeStep) 
	{
		//get the object from array
		ABA_ball* ball = BallArray[i];
		
		FVector newPos = FVector(0.0f, 0.0f, 0.0f);

		newPos.X = CalculateDisplacementX(initVelocity.X, t, ArcAngle);
		newPos.Z = CalculateDisplacementY(initVelocity.Z, t, Gravity, ArcAngle);

		//set the object's positon to the new position
		ball->SetActorRelativeLocation(newPos);
		i++;
	}
}

void UBA_ArcDrawerComponent::AdjustArcValues(float Velocity)
{
	initVelocity = FVector(Velocity, 0, Velocity);
	ArcAngle = CalculateAngle(FVector::UpVector, initVelocity);
}

float UBA_ArcDrawerComponent::CalculateAngle(FVector VectorA, FVector VectorB)
{
	float DotProduct = FVector::DotProduct(VectorA, VectorB);
	float LengthProduct = VectorA.Size() * VectorB.Size();

	float angle = FMath::Acos(DotProduct / LengthProduct);

	return angle;
}

