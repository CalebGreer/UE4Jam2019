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

	BallArray.Reserve(5);

}

float UBA_ArcDrawerComponent::CalculateDisplacementX(const float &initialVelocity, const float &time)
{
	return initialVelocity * time;
}

float UBA_ArcDrawerComponent::CalculateDisplacementY(const float & initialVelocityY, const float & time, const float & gravity)
{
	return (initialVelocityY * time) + (0.5 * gravity * (time * time));
}

// Called when the game starts
void UBA_ArcDrawerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	AActor* MyOwner = this->GetOwner();
	UWorld* World = MyOwner->GetWorld();
	Gravity = World->GetGravityZ();

	if (BallToSpawn != nullptr) {

		for (int i = 0; i < 5; i++)
		{
			FTransform ballSpawnTransform;
			ballSpawnTransform.SetLocation(MyOwner->GetActorForwardVector() * 500.0f + MyOwner->GetActorLocation());

			ABA_ball* spawnedBall = (ABA_ball*)World->SpawnActor<ABA_ball>(BallToSpawn);
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
	int i = 0;
	for (float t = 0; t < MaxTimeInterval; t += TimeStep) {

		ABA_ball* ball = BallArray[i];
		//get the object from array
		FVector newPos = FVector(0.0f, 0.0f, 0.0f);

		newPos.X = CalculateDisplacementX(initVelocity.X, t);
		newPos.Z = CalculateDisplacementY(initVelocity.Z, t, Gravity);

		//set the object's positon to the new position
		ball->SetActorRelativeLocation(newPos);
		i++;
	}

}

