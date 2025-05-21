// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkyMonster.h"
#include "TimerManager.h"
#include "TPSMonsterProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "TPSSkyMonsterAI.h"

ATPSSkyMonster::ATPSSkyMonster()
{
	AttackRange = 500.0f;
}

void ATPSSkyMonster::ShootMisile(FVector targetPosition)
{
	if (ProjectileClass)
	{
		FName SocketName = FName("Voletir_BCanonEndSocket");

		if (GetMesh()->DoesSocketExist(SocketName))
		{
			FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);

			if (UWorld* World = GetWorld())
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				ATPSMonsterProjectile* Projectile = World->SpawnActor<ATPSMonsterProjectile>(ProjectileClass,SocketLocation,FRotator::ZeroRotator,SpawnParams);
				if (Projectile)
				{
					Projectile->FireInDirection(targetPosition);
				}
			}
		}
	}
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
