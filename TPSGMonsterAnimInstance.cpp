// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGMonsterAnimInstance.h"
#include "TPS/TPSGroundMonster.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPSGMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Monster = Cast<ATPSGroundMonster>(Pawn);
	}
}

void UTPSGMonsterAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	if (Monster == nullptr) return;

	speed = Monster->GetVelocity().Size2D();
	isDead = Monster->isDead;
}
