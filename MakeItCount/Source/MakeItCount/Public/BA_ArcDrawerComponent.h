// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BA_ArcDrawerComponent.generated.h"

class ABA_ball;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAKEITCOUNT_API UBA_ArcDrawerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBA_ArcDrawerComponent();

private:

	TArray<ABA_ball*> BallArray;
	float Gravity;

	float CalculateDisplacementX(const float &initialVelocityX, const float &time);
	float CalculateDisplacementY(const float &initialVelocityY, const float &time, const float &gravity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Variables")
	float MaxTimeInterval;

	UPROPERTY(EditAnywhere, Category = "Variables")
	float TimeStep;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DrawArc(const FVector initVelocity);

	UPROPERTY(EditAnywhere, Category = "Ball")
	TSubclassOf<class ABA_ball> BallToSpawn;

	UPROPERTY(EditAnywhere, Category = "Variables")
	FVector initVelocity;
		
};
