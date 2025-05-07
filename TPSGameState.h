// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ATPSGameState();

	virtual void BeginPlay() override;

	//VALUES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 CurrentScore;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
	int32 RemainTime;

};
