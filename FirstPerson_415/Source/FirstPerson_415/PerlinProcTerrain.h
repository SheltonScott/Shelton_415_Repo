// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

// Declare classes
class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class FIRSTPERSON_415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// Declare x and y size variables
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	// Declare z multiplier and noise scale variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	// Declare UV scale and scale variables
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0;

	// Declare radius and depth variables
	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(EditAnywhere)
	FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Declare material variable
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to alter a mesh
	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	// Declare variables for procedural mesh, vertices, triangles, uvs, normals, and upvertex colors
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	// Declare a variable for the section id
	int sectionID = 0;

	// Declare classes to generate vertices and triangles
	void CreateVertices();
	void CreateTriangles();

};
