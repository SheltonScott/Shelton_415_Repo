// Fill out your copyright notice in the Description page of Project Settings.


#include "Portals.h"
#include "FirstPerson_415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortals::APortals()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize necessary components
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow"); // Initialize new arrow component

	// Setup attachments
	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent); // Attach the root arrow to the box component

	// Disable collisions for the mesh
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortals::BeginPlay()
{
	Super::BeginPlay();

	// Setup dynamic component
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortals::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);

	// If the mat variable is set then set the material
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Call update portals
	UpdatePortals();

}

// Call when the character is overlapping with a portal
void APortals::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Cast to the first person character
	AFirstPerson_415Character* playerChar = Cast<AFirstPerson_415Character>(OtherActor);

	// If the player character is valid
	if (playerChar)
	{
		// If the other portal is valid
		if (OtherPortal)
		{
			// If the player character is not "teleporting"
			if (!playerChar->isTeleporting)
			{
				// Set the player to "teleporting" and change the location to the other portal
				playerChar->isTeleporting = true;
				// FVector loc = OtherPortal->GetActorLocation();
				FVector loc = OtherPortal->rootArrow->GetComponentLocation(); // Change the set location to the root arrow instead of the box component
				playerChar->SetActorLocation(loc);

				// Delay then reset the to player to not "teleporting"
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}

// Call to change the value of the boolean
void APortals::SetBool(AFirstPerson_415Character* playerChar)
{
	// If the player character is valid
	if (playerChar)
	{
		// Set the player to not "teleporting"
		playerChar->isTeleporting = false;
	}
}

// Call to update the portals
void APortals::UpdatePortals()
{
	// Create a local vector variable to get and store the difference between the portals
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();

	// Create local variables to get and store the player camera location and rotation
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();

	// Calculate the combined location
	FVector CombinedLocation = camLocation + Location;

	// Set the world location and rotation of scene capture component
	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

