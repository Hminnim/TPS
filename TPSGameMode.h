// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameMode.generated.h"

class UTPSUserWidget;
/**
 * 
 */
UCLASS()
class TPS_API ATPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// FUNCTION
	void SetWidget();
	void SetAmmo(int32 currentAmmo, int32 maxAmmo);
	void UpdateAmmo(int32 AmmoChange);
	void UpdateCrosshair(bool isShow);
	void UpdateScore(int32 scoreChange);
	

protected:
	int32 CurrentAmmo = 0;
	int32 MaxAmmo = 0;
	int32 CurrentScore = 0;
	int32 CurrentTime = 0;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	UTPSUserWidget* GameWidget;

	virtual void BeginPlay() override;
	void UpdateAmmoText();

};
