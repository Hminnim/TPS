// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "TPSSkyMonsterAI.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSSkyMonsterAI : public AAIController
{
	GENERATED_BODY()

public:
	ATPSSkyMonsterAI();

	// Function
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	void StopAI();

private:

	// BehaviorTree, BlackBoard
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UBehaviorTree> BT_Monster;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UBlackboardData> BB_Monster;

	// AI perception component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	class UAIPerceptionComponent* AIPerception;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	class UAISenseConfig_Damage* DamageConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
