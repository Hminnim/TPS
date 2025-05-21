// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSMonster.h"
#include "TPSSkyMonster.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSSkyMonster : public ATPSMonster
{
	GENERATED_BODY()
	
public:
	ATPSSkyMonster();

	// VALUES //
	FTimerHandle DeathTimer;

	// FUNCTION //
	void ShootMisile(FVector targetPosition);
	virtual void DestroyMonster() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class ATPSMonsterProjectile> ProjectileClass;
};
