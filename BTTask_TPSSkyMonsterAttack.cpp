// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TPSSkyMonsterAttack.h"
#include "AIController.h"
#include "TPSSkyMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TPSSkyMonsterAttack::UBTTask_TPSSkyMonsterAttack()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_TPSSkyMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIPawn Failed")));

		return EBTNodeResult::Failed;
	}

	AIMonster = Cast<ATPSSkyMonster>(AIPawn);
	if (AIMonster == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIMonster Failed")));

		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (Target == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Target Failed")));

		return EBTNodeResult::Failed;
	}

	AIMonster->ShootMisile(Target->GetActorLocation());

	return EBTNodeResult::Succeeded;
}
