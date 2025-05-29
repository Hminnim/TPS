// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSHealthBar.h"

void UTPSHealthBar::SetHPBar(float CurrentHP, float MaxHP)
{
	float HPRatio = CurrentHP / MaxHP;
	HealthPointBar->SetPercent(HPRatio);
}
