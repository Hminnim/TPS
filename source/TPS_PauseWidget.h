// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPS_PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPS_PauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	// Bind widget
	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* TitleButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

private:
	// Widget function
	UFUNCTION()
	void OnOptionButtonClicked();
	UFUNCTION()
	void OnTitleButtonClicked();
	UFUNCTION()
	void OnBackButtonClicked();
};
