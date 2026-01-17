// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSSMonsterAnimInstance.generated.h"

class ATPSSkyMonster;

/**
 * 
 */
UCLASS()
class TPS_API UTPSSMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ATPSSkyMonster* Monster;

public:
	// Function
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecond) override;

	// Monster values
	UPROPERTY(BlueprintReadWrite)
	float MonsterSpeed;
	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;
};
