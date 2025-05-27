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
	// FUNCTION //
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecond) override;

	// VALUES //
	UPROPERTY(BlueprintReadWrite)
	bool isAim;
	UPROPERTY(BlueprintReadWrite)
	bool isShoot;
	UPROPERTY(BlueprintReadWrite)
	bool isFalling;
	UPROPERTY(BlueprintReadWrite)
	bool isReload;
	UPROPERTY(BlueprintReadWrite)
	float speed;
	UPROPERTY(BlueprintReadWrite)
	float direction;
	UPROPERTY(BlueprintReadWrite)
	float AimYaw;
	UPROPERTY(BlueprintReadWrite)
	float AimPitch;;
};
