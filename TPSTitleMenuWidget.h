// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSTitleMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSTitleMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* StartButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* QuitButton;

private:
	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnQuickButtonClicked();
};
