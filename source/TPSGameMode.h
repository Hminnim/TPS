// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameMode.generated.h"

class UTPSUserWidget;
class UTPSGameOverWidget;
class UTPS_PauseWidget;
class UTPSOptionWidget;
class ATPSMonsterSpawner;
/**
 * 
 */
UCLASS()
class TPS_API ATPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Function
	void SetWidget();
	void UpdateAmmo(int32 CurrentAmmo, int32 MaxAmmo);
	void UpdateCrosshair(bool bIsShow);
	void UpdateScore(int32 scoreChange);
	void UpdateTimer();
	void StartTImer();
	void GameOver();
	void GamePause();
	void GameResume();
	void OpenOption();
	void CloseOption();
	void SetHealthBar(float MaxHealth, float CurrentHealth);

protected:
	virtual void BeginPlay() override;
	
	// Game value
	int32 CurrentScore = 0;
	int32 CurrentTime = 120;	

	// Widget
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> GameWidgetClass;
	UPROPERTY()
	UTPSUserWidget* GameWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UTPSGameOverWidget> GameoverWidgetClass;
	UPROPERTY()
	UTPSGameOverWidget* GameoverWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UTPS_PauseWidget> PauseWidgetClass;
	UPROPERTY()
	UTPS_PauseWidget* PauseWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UTPSOptionWidget> OptionWidgetClass;
	UTPSOptionWidget* OptionWidget;

	// Monster spawner
	UPROPERTY(EditAnywhere, Category = "Monster Spawner")
	TSubclassOf<class ATPSMonsterSpawner> MonsterSpawnerClass;
	ATPSMonsterSpawner* MonsterSpawner;
	void StartMonsterSpawn();

private:
	FTimerHandle timerHandle;
};
