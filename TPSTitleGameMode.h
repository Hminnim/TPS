// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSTitleGameMode.generated.h"

class UTPSTitleMenuWidget;
/**
 * 
 */
UCLASS()
class TPS_API ATPSTitleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSTitleGameMode();
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	UTPSTitleMenuWidget* GameWidget;

};
