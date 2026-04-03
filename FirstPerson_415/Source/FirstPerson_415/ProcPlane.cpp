// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcPlane.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProcPlane::AProcPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create default subobject for proc mesh
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");

}

// Called when the game starts or when spawned
void AProcPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Call when actor has been created
void AProcPlane::PostActorCreated()
{
	Super::PostActorCreated();
	// Call create mesh function
	CreateMesh();

	// Set proc mesh material to plane mat if it is set
	if (PlaneMat)
	{
		procMesh->SetMaterial(0, PlaneMat);
	}
}

// Call when the game loads
void AProcPlane::PostLoad()
{
	Super::PostLoad();
	// Call create mesh function
	CreateMesh();

	// Set proc mesh material to plane mat if it is set
	if (PlaneMat)
	{
		procMesh->SetMaterial(0, PlaneMat);
	}
}

// Called every frame
void AProcPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcPlane::CreateMesh()
{
	// Create a procedural mesh section
	procMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

