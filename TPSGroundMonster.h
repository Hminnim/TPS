// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSMonster.h"
#include "TPSGroundMonster.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSGroundMonster : public ATPSMonster
{
	GENERATED_BODY()
	

public:
	ATPSGroundMonster();

	// VALUES //
	FTimerHandle DeathTimer;

	// FUNCTION //
	void MeleeAttack(AActor* target);
	virtual void DestroyMonster() override;

protected:
};
