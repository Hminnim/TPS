// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSMonsterAnimInstance.h"
#include "TPSSkyMonster.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPSSMonsterAnimInstance::NativeBeginPlay()
{
	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Monster = Cast<ATPSSkyMonster>(Pawn);
	}
}

void UTPSSMonsterAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	if (Monster == nullptr) return;

	speed = Monster->GetVelocity().Size2D();
	isDead = Monster->isDead;
}
