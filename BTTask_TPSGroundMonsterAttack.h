// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TPSGroundMonsterAttack.generated.h"

/**
 * 
 */
class ATPSGroundMonster;

UCLASS()
class TPS_API UBTTask_TPSGroundMonsterAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TPSGroundMonsterAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	ATPSGroundMonster* AIMonster;
};
