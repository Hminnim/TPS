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
	MaxHealthPoint = 80.0f;
	HealthPoint = 80.0f;
}

void ATPSSkyMonster::ShootMisile(FVector targetPosition)
{
	if (ProjectileClass)
	{
		FName SocketName = FName(TEXT("Voletir_BCanonEndSocket"));

		if (GetMesh()->DoesSocketExist(SocketName))
		{
			FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);
			FVector Direction = (targetPosition - SocketLocation).GetSafeNormal();
			FRotator FireRotation = Direction.Rotation();

			if (UWorld* World = GetWorld())
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


				ATPSMonsterProjectile* Projectile = World->SpawnActor<ATPSMonsterProjectile>(
					ProjectileClass,
					SocketLocation,
					FireRotation,
					SpawnParams
				);
				if (Projectile)
				{
					Projectile->FireInDirection(Direction);
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
	bIsDead = true;

	Super::DestroyMonster();

	this->Destroy();
}
