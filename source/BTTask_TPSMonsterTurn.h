// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TPSMonsterTurn.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UBTTask_TPSMonsterTurn : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TPSMonsterTurn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

};
