// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetAmmoText(int32 currentAmmo, int32 maxAmmo);
	void ShowCrosshair(bool isShow);
	void SetScoreText(int32 CurrentScore);
	void SetTimerText(int32 CurrentTime);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Score;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentAmmo;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmo;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Timer;
	UPROPERTY(meta = (BindWidget))
	class UImage* Crosshair;
};
