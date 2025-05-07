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

	UFUNCTION(BlueprintImplementableEvent)
	void SetAmmoText(int32 CurrentAmmo, int32 MaxAmmo);
	UFUNCTION(BlueprintImplementableEvent)
	void ShowCrosshair(bool isShow);
};
