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
	// Widget function
	void SetAmmoText(int32 CurrentAmmo, int32 MaxAmmo);
	void ShowCrosshair(bool bIsShow);
	void SetScoreText(int32 CurrentScore);
	void SetTimerText(int32 CurrentTime);
	void SetHealthBar(float MaxHealth, float CurrentHealth);

protected:
	// Bind widget
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Score;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Ammo;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Timer;
	UPROPERTY(meta = (BindWidget))
	class UImage* Crosshair;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};
