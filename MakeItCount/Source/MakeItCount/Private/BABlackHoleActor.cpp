// Fill out your copyright notice in the Description page of Project Settings.


#include "BABlackHoleActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABABlackHoleActor::ABABlackHoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
 
	GravityCollider = CreateDefaultSubobject<USphereComponent>(TEXT("GravityRange"));
	GravityCollider->SetSphereRadius(GravityRadius);
	GravityCollider->SetupAttachment(MeshComp);

	DestroyerComp = CreateDefaultSubobject<USphereComponent>(TEXT("Destroyer"));
	DestroyerComp->SetupAttachment(MeshComp);
	DestroyerComp->SetSphereRadius(DestroyRadius);
	DestroyerComp->OnComponentBeginOverlap.AddDynamic(this, &ABABlackHoleActor::OverlapInnerSphere);
}

// Called when the game starts or when spawned
void ABABlackHoleActor::BeginPlay()
{
	Super::BeginPlay(); 
}

void ABABlackHoleActor::GravityTick()
{
	TArray<UPrimitiveComponent*> comps;
	GravityCollider->GetOverlappingComponents(comps);

	for (auto comp : comps)
	{ 
		if (comp->IsSimulatingPhysics())
		{
			comp->AddRadialForce(GetActorLocation(), GravityCollider->GetScaledSphereRadius(), -PullingForce, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

void ABABlackHoleActor::OverlapInnerSphere(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		OtherActor->Destroy();
		Kills++;
	}
}

// Called every frame
void ABABlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	GravityTick();
}

