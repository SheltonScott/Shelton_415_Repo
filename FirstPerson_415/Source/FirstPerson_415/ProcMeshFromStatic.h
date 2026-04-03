// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMeshFromStatic.generated.h"

UCLASS()
class FIRSTPERSON_415_API AProcMeshFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMeshFromStatic();

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

	// Declare necessary array variables
	// vertices is an array of FVectors
	UPROPERTY()
	TArray<FVector> Vertices;

	// triangles is an array of integers
	UPROPERTY()
	TArray<int> Triangles;

	// normals is an array of FVectors
	UPROPERTY()
	TArray<FVector> Normals;

	// uv0 is an array of 2D FVectors
	TArray<FVector2D> UV0;

	// vertex colors is an array of FColors
	UPROPERTY()
	TArray<FColor> VertexColors;

	// up vertex colors is an array of FColors
	TArray<FColor> UpVertexColors;

	// tangents is an array of FProcMeshTangents
	TArray<FProcMeshTangent> Tangents;

	// Declare a variable for the base mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* baseMesh;

private:
	// Declare a variable for the procedural mesh
	UProceduralMeshComponent* procMesh;

	// Declare a function to receive mesh data
	void GetMeshData();

	// Declare a function to create the mesh
	void CreateMesh();

};
