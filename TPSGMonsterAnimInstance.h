// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSGMonsterAnimInstance.generated.h"

class ATPSGroundMonster;

/**
 * 
 */
UCLASS()
class TPS_API UTPSGMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ATPSGroundMonster* Monster;

public:
	// FUNCTION //
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecond) override;

	// VALUES //
	UPROPERTY(BlueprintReadWrite)
	float speed;
	UPROPERTY(BlueprintReadWrite)
	bool isDead;
};
