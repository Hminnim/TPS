// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TPSMonsterTurn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TPSMonsterTurn::UBTTask_TPSMonsterTurn()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_TPSMonsterTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AIPawn Failed")));

		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (Target == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Target Failed")));

		return EBTNodeResult::Failed;
	}

	FRotator LookAtRotation = (Target->GetActorLocation() - AIPawn->GetActorLocation()).Rotation();
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;

	AIPawn->SetActorRotation(LookAtRotation);

	return EBTNodeResult::Succeeded;
}
