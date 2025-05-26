// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSMonsterSpawner.generated.h"

class ATPSMonster;

UCLASS()
class TPS_API ATPSMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ATPSMonsterSpawner();

	// FUNCTION //
	void StartSpawning();
	void StopSpawning();

	// VALUES //
	int32 monstersCount;
	float spawnPeriod;

protected:
	// FUNCTION //
	void SpawnMonster();

	// Monsters //
	ATPSMonster* Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monsters")
	TArray<TSubclassOf<ATPSMonster>> MonsterClasses;

	// VALUES //
	FTimerHandle spawnTimerHandle;
};
