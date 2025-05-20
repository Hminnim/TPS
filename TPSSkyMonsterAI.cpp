// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkyMonsterAI.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TPSCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AIPerceptionTypes.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Damage.h>

ATPSSkyMonsterAI::ATPSSkyMonsterAI()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	// Sight Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 1000.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	// Damage Config
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));

	AIPerception->ConfigureSense(*DamageConfig);

	// Binding
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ATPSSkyMonsterAI::PerceptionUpdated);
}

void ATPSSkyMonsterAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetGenericTeamId(FGenericTeamId(1));

	UBlackboardComponent* bbComponent = Blackboard.Get();
	if (UseBlackboard(BB_Monster, bbComponent))
	{
		APawn* TargetPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();

		Blackboard->SetValueAsObject(TEXT("Player"), TargetPlayer);
		Blackboard->SetValueAsVector(TEXT("HomePosition"), GetPawn()->GetActorLocation());
		bool RunResult = RunBehaviorTree(BT_Monster);
	}
}

void ATPSSkyMonsterAI::OnUnPossess()
{
	Super::OnUnPossess();
}

void ATPSSkyMonsterAI::StopAI()
{
	if (UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		BTComponent->StopTree(EBTStopMode::Forced);
	}
	StopMovement();
}

void ATPSSkyMonsterAI::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsBool(TEXT("CanDetect"), true);
	}
}
