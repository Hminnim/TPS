// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSHealthBar.h"

void UTPSHealthBar::SetHPBar(float curHP, float maxHP)
{
	float HPRatio = curHP / maxHP;
	HealthPointBar->SetPercent(HPRatio);
}
