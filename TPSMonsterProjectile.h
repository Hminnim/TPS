// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "TPSMonsterProjectile.generated.h"

UCLASS()
class TPS_API ATPSMonsterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATPSMonsterProjectile();

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	UParticleSystem* ExplosionEffect;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void FireInDirection(const FVector& ShootDirection);

protected:
	float ExplosionRadius = 150.0f;
	float ExplosionDamage = 10.0f;
};
