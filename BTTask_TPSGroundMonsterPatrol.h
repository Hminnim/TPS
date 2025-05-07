// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TPSGroundMonsterPatrol.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UBTTask_TPSGroundMonsterPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_TPSGroundMonsterPatrol();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
