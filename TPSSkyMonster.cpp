// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkyMonster.h"
#include "TimerManager.h"
#include <Kismet/GameplayStatics.h>
#include "TPSSkyMonsterAI.h"

ATPSSkyMonster::ATPSSkyMonster()
{
	AttackRange = 500.0f;
}

void ATPSSkyMonster::ShootMisile(FVector targetPosition)
{

}

void ATPSSkyMonster::DestroyMonster()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (ATPSSkyMonsterAI* MonsterAI = Cast<ATPSSkyMonsterAI>(AIController))
		{
			MonsterAI->StopAI();
		}
	}
	isDead = true;

	Super::DestroyMonster();

	this->Destroy();
}
