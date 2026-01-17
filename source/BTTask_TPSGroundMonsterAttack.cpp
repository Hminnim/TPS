// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TPSGroundMonsterAttack.h"
#include "AIController.h"
#include "TPSGroundMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TPSGroundMonsterAttack::UBTTask_TPSGroundMonsterAttack()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_TPSGroundMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	// Exception handling
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIPawn Failed")));

		return EBTNodeResult::Failed;
	}

	AIMonster = Cast<ATPSGroundMonster>(AIPawn);
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

	// Check distance between monster and player
	double Distance = FVector::Distance(AIPawn->GetActorLocation(), Target->GetActorLocation());
	if (Distance <= AIMonster->AttackRange)
	{
		AIMonster->MeleeAttack(Target);
	}

	return EBTNodeResult::Succeeded;
}
