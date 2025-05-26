// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSMonsterSpawner.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "TPSMonster.h"

// Sets default values
ATPSMonsterSpawner::ATPSMonsterSpawner()
{
	monstersCount = 0;
	spawnPeriod = 5.0f;
}

void ATPSMonsterSpawner::StartSpawning()
{
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &ATPSMonsterSpawner::SpawnMonster, spawnPeriod, true, 5.0f);
}

void ATPSMonsterSpawner::StopSpawning()
{
	GetWorld()->GetTimerManager().ClearTimer(spawnTimerHandle);
}

void ATPSMonsterSpawner::SpawnMonster()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr) return;

	FNavLocation Randomlocation;
	NavSystem->GetRandomPoint(Randomlocation);

	int32 randomMonster = FMath::RandRange(0, MonsterClasses.Num() - 1);

	if (MonsterClasses[randomMonster] == nullptr) return;
	if (GetWorld()->SpawnActor<ATPSMonster>(MonsterClasses[randomMonster], Randomlocation.Location, FRotator::ZeroRotator))
	{
		monstersCount++;
	}

}
