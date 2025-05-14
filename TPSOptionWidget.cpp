// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSOptionWidget.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"

bool UTPSOptionWidget::Initialize()
{
	Super::Initialize();

	if (FullscreenCheckBox)
	{
		FullscreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UTPSOptionWidget::OnFullscreenCheckChanged);
	}
	if (ResolutionComboBox)
	{

	}
	if (VolumeSlider)
	{

	}

	return true;
}

void UTPSOptionWidget::OnFullscreenCheckChanged(bool isChecked)
{
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		Settings->SetFullscreenMode(isChecked ? EWindowMode::Fullscreen : EWindowMode::Windowed);
	}
}
