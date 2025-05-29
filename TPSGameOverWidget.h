// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	// Bind widget
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* TitleButton;

private:
	// Widget function
	UFUNCTION()
	void OnRestartButtonClicked();
	UFUNCTION()
	void OnTitleButtonClicked();
};
