// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TPSMonsterCheckRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSMonster.h"
#include "AIController.h"

UBTService_TPSMonsterCheckRange::UBTService_TPSMonsterCheckRange()
{
}

void UBTService_TPSMonsterCheckRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Exception handling
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIPawn Failed")));

		return;
	}

	AIMonster = Cast<ATPSMonster>(AIPawn);
	if (AIMonster == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIMonster Failed")));

		return;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (Target == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Target Failed")));

		return;
	}

	double Distance = FVector::Distance(AIPawn->GetActorLocation(), Target->GetActorLocation());
	if (Distance <= AIMonster->AttackRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), true);
		
		return;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), false);

		return;
	}

	return;
}
