// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAnimInstance.h"
#include "TPS/TPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>


void UTPSAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Character = Cast<ATPSCharacter>(Pawn);
	}
}

void UTPSAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	if (Character == nullptr)
	{
		return;
	}

	FRotator ControlRotation = Character->GetControlRotation();
	FRotator ActorRotation = Character->GetActorRotation();
	FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, ActorRotation);

	AimYaw = DeltaRotation.Yaw;
	AimPitch = DeltaRotation.Pitch;

	CharacterSpeed = Character->GetVelocity().Size2D();
	bIsFalling = Character->GetCharacterMovement()->IsFalling();
	bIsAim = Character->IsAiming();
	bIsShoot = Character->IsShooting();
	bIsReload = Character->IsRealoading();
	CharacterDirection = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}