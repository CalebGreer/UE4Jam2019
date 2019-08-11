// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BABlackHoleActor.generated.h"

class USphereComponent;

UCLASS()
class MAKEITCOUNT_API ABABlackHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABABlackHoleActor();

protected: 

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DestroyerComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* GravityCollider;

	UPROPERTY(EditInstanceOnly, Category = "Properties")
	float GravityRadius = 1000.0f; 

	UPROPERTY(EditInstanceOnly, Category = "Properties")
	float DestroyRadius = 100.0f;

	UPROPERTY(EditInstanceOnly, Category = "Properties")
	float Power = 20000.0f; 

	UPROPERTY(EditInstanceOnly, Category = "Properties")
	float PullingForce = 2000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GravityTick();

	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
