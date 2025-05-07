// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TPSGroundMonsterPatrol.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TPSGroundMonsterPatrol::UBTTask_TPSGroundMonsterPatrol()
{
}

EBTNodeResult::Type UBTTask_TPSGroundMonsterPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIPawn Failed")));

		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(AIPawn->GetWorld());
	if (NavSystem == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("NavSystem Failed")));

		return EBTNodeResult::Failed;
	}

	FVector HomePosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomePosition"));
	FNavLocation PatrolPosition;

	if (NavSystem->GetRandomPointInNavigableRadius(HomePosition, 1000.0f, PatrolPosition))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPosition"), PatrolPosition);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Patrol")));

		return EBTNodeResult::Succeeded;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("UBTTask_TPSGroundMonsterPatrol Failed")));

	return EBTNodeResult::Failed;
}
