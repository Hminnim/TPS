// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Own Character", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class ATPSCharacter> ownCharacter;
};
