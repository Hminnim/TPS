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
}

void ATPSSkyMonsterAI::OnPossess(APawn* InPawn)
{
}

void ATPSSkyMonsterAI::OnUnPossess()
{
}

void ATPSSkyMonsterAI::StopAI()
{
}

void ATPSSkyMonsterAI::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}
