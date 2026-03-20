// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstPerson_415Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AFirstPerson_415Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// Reference to static mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ballMesh;

	// UMaterial for baseMat
	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	// Create the uproperty for randColor here first
	UPROPERTY()
	FLinearColor randColor;

	// UMaterial for projMat
	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

	// Dynamic instance uproperty
	UMaterialInstanceDynamic* dmiMat;

public:
	AFirstPerson_415Projectile();

protected:
	virtual void BeginPlay();

	
public:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

