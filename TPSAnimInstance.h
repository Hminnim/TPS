// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSAnimInstance.generated.h"

class ATPSCharacter;

/**
 * 
 */
UCLASS()
class TPS_API UTPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ATPSCharacter* Character;

public:
	// Function
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecond) override;

	// Character state values
	UPROPERTY(BlueprintReadWrite)
	bool bIsAim;
	UPROPERTY(BlueprintReadWrite)
	bool bIsShoot;
	UPROPERTY(BlueprintReadWrite)
	bool bIsFalling;
	UPROPERTY(BlueprintReadWrite)
	bool bIsReload;
	UPROPERTY(BlueprintReadWrite)
	float CharacterSpeed;
	UPROPERTY(BlueprintReadWrite)
	float CharacterDirection;
	UPROPERTY(BlueprintReadWrite)
	float AimYaw;
	UPROPERTY(BlueprintReadWrite)
	float AimPitch;;
};
