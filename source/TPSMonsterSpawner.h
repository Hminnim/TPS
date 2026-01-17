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

	// Function
	void StartSpawning();
	void StopSpawning();

	// Value
	int32 MonsterCount;
	float SpawnPeriod;

protected:
	// Function
	void SpawnMonster();

	// For monsters
	ATPSMonster* Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monsters")
	TArray<TSubclassOf<ATPSMonster>> MonsterClasses;

	// Value
	FTimerHandle spawnTimerHandle;
};
