// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPerson_415PickUpComponent.h"

UFirstPerson_415PickUpComponent::UFirstPerson_415PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UFirstPerson_415PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UFirstPerson_415PickUpComponent::OnSphereBeginOverlap);
}

void UFirstPerson_415PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AFirstPerson_415Character* Character = Cast<AFirstPerson_415Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
