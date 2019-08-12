// Fill out your copyright notice in the Description page of Project Settings.


#include "BAProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BABlackHoleActor.h"

// Sets default values
ABAProjectile::ABAProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->InitSphereRadius(.2f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABAProjectile::OnHit);

	RootComponent = CollisionComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->bAutoActivate = false;
	//MovementComp->InitialSpeed = 0.0f;
	//MovementComp->MaxSpeed = 0.0f; 
}

void ABAProjectile::PlaySpawn()
{
	GetWorld()->SpawnActor<AActor>(BlackHoleBP, GetTransform());
}

void ABAProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	PlaySpawn();
	Destroy();
}

void ABAProjectile::LaunchProjectile(float Speed)
{
	MovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComp->Activate();
}
