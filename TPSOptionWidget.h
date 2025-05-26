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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Class")
	class USoundClass* MasterSoundClass;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* FullscreenCheckBox;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ResolutionComboBox;
	UPROPERTY(meta = (BindWidget))
	class USlider* VolumeSlider;
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UFUNCTION()
	void OnFullscreenCheckChanged(bool bIsChecked);
	UFUNCTION()
	void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void OnMasterVolumeChanged(float Value);
	UFUNCTION()
	void OnBackButtonClicked();
};
