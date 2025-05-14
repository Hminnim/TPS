// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSOptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* FullscreenCheckBox;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ResolutionComboBox;
	UPROPERTY(meta = (BindWidget))
	class USlider* VolumeSlider;

	void OnFullscreenCheckChanged(bool isChecked);
	void SetResolution();
	void SetMasterVolume(float Volume);
};
