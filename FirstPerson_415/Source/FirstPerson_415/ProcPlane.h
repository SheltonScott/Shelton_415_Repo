// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

// Declare procedural mesh component class
class UProceduralMeshComponent;

UCLASS()
class FIRSTPERSON_415_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Call when actor has been created
	virtual void PostActorCreated() override;

	// Call when the game loads
	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Declare vertices and triangles variables
	// vertices is an array of vectors
	UPROPERTY(EditAnywhere)
	TArray<FVector> Vertices;

	// triangles is an array of integers
	UPROPERTY(EditAnywhere)
	TArray<int> Triangles;

	// Declare an array for the UVs
	UPROPERTY(EditAnywhere)
	TArray<FVector2D> UV0;

	// Declare a material variable
	UPROPERTY(EditAnywhere)
	UMaterialInterface* PlaneMat;

	// Declare create mesh function
	void CreateMesh();

private:
	// Declare procedural mesh component
	UProceduralMeshComponent* procMesh;

};
