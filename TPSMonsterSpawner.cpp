// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSMonsterSpawner.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "TPSMonster.h"

// Sets default values
ATPSMonsterSpawner::ATPSMonsterSpawner()
{
	monstersCount = 0;
	spawnPeriod = 10.0f;
}

void ATPSMonsterSpawner::StartSpawning()
{
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &ATPSMonsterSpawner::SpawnMonster, spawnPeriod, true, 10.0f);
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

	if (MonsterClass == nullptr) return;
	if (GetWorld()->SpawnActor<ATPSMonster>(MonsterClass, Randomlocation.Location, FRotator::ZeroRotator))
	{
		monstersCount++;
	}

}
