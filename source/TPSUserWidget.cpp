// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UTPSUserWidget::SetAmmoText(int32 CurrentAmmo, int32 MaxAmmo)
{
	FString AmmoText = FString::Printf(TEXT("%d / %d"), CurrentAmmo, MaxAmmo);
	Ammo->SetText(FText::FromString(AmmoText));
}

void UTPSUserWidget::ShowCrosshair(bool bIsShow)
{
	if (bIsShow)
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Crosshair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTPSUserWidget::SetScoreText(int32 CurrentScore)
{
	Score->SetText(FText::AsNumber(CurrentScore));
}

void UTPSUserWidget::SetTimerText(int32 CurrentTime)
{
	Timer->SetText(FText::AsNumber(CurrentTime));
}

void UTPSUserWidget::SetHealthBar(float MaxHealth, float CurrentHealth)
{
	float Ratio = CurrentHealth / MaxHealth;
	HealthBar->SetPercent(Ratio);
}
