// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portals.generated.h"

// Forward declaration for the player character
class FirstPerson_415Character;

UCLASS()
class FIRSTPERSON_415_API APortals : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Declare variables for the mesh, scene capture component and render target
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow; // Added an arrow to manipulate where the player spawns on "teleport"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	// Declare variables for the box component, the other "portal" and the material
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	APortals* OtherPortal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

	// Declare an overlap event and function to change the boolean and update the portals
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetBool(AFirstPerson_415Character* playerChar);

	UFUNCTION()
	void UpdatePortals();

};
