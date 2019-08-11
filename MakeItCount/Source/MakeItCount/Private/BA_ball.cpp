// Fill out your copyright notice in the Description page of Project Settings.


#include "BA_ball.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
ABA_ball::ABA_ball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}


// Called when the game starts or when spawned
void ABA_ball::BeginPlay()
{
	Super::BeginPlay();

}