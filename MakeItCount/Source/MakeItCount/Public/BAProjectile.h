// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BAProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MAKEITCOUNT_API ABAProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABAProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	UClass* BlackHoleBP;

protected:
	void PlaySpawn();

public:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UProjectileMovementComponent* GetProjectileMovement() const { return MovementComp; }

	void LaunchProjectile(float Speed);

};
