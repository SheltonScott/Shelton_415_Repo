// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshFromStatic::AProcMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create the default subobjects for the proc mesh and base mesh
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");

	// Set up attachments
	// procMesh->SetupAttachment(GetRootComponent());
	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);

}

// Called when the game starts or when spawned
void AProcMeshFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshFromStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProcMeshFromStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

// Called to receive mesh data
void AProcMeshFromStatic::GetMeshData()
{
	// Create local static mesh variable using the static mesh from base mesh
	UStaticMesh* mesh = baseMesh->GetStaticMesh();

	// If mesh is set
	if (mesh)
	{
		// Pass mesh to the function to pull data from the static mesh and generate a procedural mesh from it
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

// Called to generate procedural mesh
void AProcMeshFromStatic::CreateMesh()
{
	// If base mesh is set
	if (baseMesh)
	{
		// Create the procedural mesh
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

// Called every frame
void AProcMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

