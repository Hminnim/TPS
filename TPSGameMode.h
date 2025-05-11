// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameMode.generated.h"

class UTPSUserWidget;
class ATPSMonsterSpawner;
/**
 * 
 */
UCLASS()
class TPS_API ATPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// FUNCTION //
	void SetWidget();
	void SetAmmo(int32 currentAmmo, int32 maxAmmo);
	void UpdateAmmo(int32 AmmoChange);
	void UpdateCrosshair(bool isShow);
	void UpdateScore(int32 scoreChange);
	void UpdateTimer();
	void StartTImer();

protected:
	int32 CurrentAmmo = 0;
	int32 MaxAmmo = 0;
	int32 CurrentScore = 0;
	int32 CurrentTime = 0;

	virtual void BeginPlay() override;

	// Widget //
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> GameWidgetClass;
	UPROPERTY()
	UTPSUserWidget* GameWidget;

	// Monster Spawner //
	UPROPERTY(EditAnywhere, Category = "Monster Spawner")
	TSubclassOf<class ATPSMonsterSpawner> MonsterSpawnerClass;
	ATPSMonsterSpawner* MonsterSpawner;
	void StartMonsterSpawn();

	// Ammo //
	void UpdateAmmoText();

private:
	FTimerHandle timerHandle;

};
