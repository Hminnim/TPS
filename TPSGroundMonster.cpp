// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGroundMonster.h"
#include "TPSGroundMonsterAI.h"
#include "TimerManager.h"
#include <Kismet/GameplayStatics.h>

ATPSGroundMonster::ATPSGroundMonster()
{
	AttackRange = 300.0f;
	MaxHealthPoint = 150.0f;
	HealthPoint = 150.0f;
}

void ATPSGroundMonster::MeleeAttack(AActor* target)
{
	UGameplayStatics::ApplyDamage(target, AttackDamage,this->GetController(),this, UDamageType::StaticClass());
	if (AttackSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
	}
}

void ATPSGroundMonster::DestroyMonster()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (ATPSGroundMonsterAI* MonsterAI = Cast<ATPSGroundMonsterAI>(AIController))
		{
			MonsterAI->StopAI();
		}
	}
	bIsDead = true;
	
	Super::DestroyMonster();

	GetWorld()->GetTimerManager().SetTimer(
		DeathTimer,  
		FTimerDelegate::CreateLambda([&]() {
			this->Destroy();
		}),
		0.67f,                             
		false                        
	);
	
}
