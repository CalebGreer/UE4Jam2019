// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BA_ball.generated.h"

UCLASS()
class MAKEITCOUNT_API ABA_ball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABA_ball();

protected:

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;

public:
	void BeginPlay();

};
