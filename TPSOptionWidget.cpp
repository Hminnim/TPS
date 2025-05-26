// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSOptionWidget.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Sound/SoundClass.h"
#include "TPSGameMode.h"
#include "GameFramework/GameUserSettings.h"

bool UTPSOptionWidget::Initialize()
{
	Super::Initialize();

	UGameUserSettings* Settings = GEngine->GetGameUserSettings();

	if (FullscreenCheckBox)
	{
		FullscreenCheckBox->SetIsChecked(Settings->GetFullscreenMode() == EWindowMode::Fullscreen);
		FullscreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UTPSOptionWidget::OnFullscreenCheckChanged);
	}
	if (ResolutionComboBox)
	{
		FIntPoint Resolution = Settings->GetScreenResolution();
		FString CurrentResolution = FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y);

		ResolutionComboBox->AddOption(TEXT("960x540"));
		ResolutionComboBox->AddOption(TEXT("1280x720"));
		ResolutionComboBox->AddOption(TEXT("1920x1080"));
		ResolutionComboBox->AddOption(TEXT("2560x1440"));
		ResolutionComboBox->SetSelectedOption(CurrentResolution);
		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UTPSOptionWidget::OnResolutionChanged);
	}
	if (VolumeSlider)
	{
		if (MasterSoundClass)
		{
			VolumeSlider->SetValue(MasterSoundClass->Properties.Volume);
		}
		VolumeSlider->OnValueChanged.AddDynamic(this, &UTPSOptionWidget::OnMasterVolumeChanged);
	}
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UTPSOptionWidget::OnBackButtonClicked);
	}

	return true;
}

void UTPSOptionWidget::OnFullscreenCheckChanged(bool bIsChecked)
{
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		Settings->SetFullscreenMode(bIsChecked ? EWindowMode::Fullscreen : EWindowMode::Windowed);
		Settings->ApplySettings(false);
	}
}

void UTPSOptionWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	TArray<FString> Split;
	SelectedItem.ParseIntoArray(Split, TEXT("x"));

	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		FIntPoint NewResoltuion = { FCString::Atoi(*Split[0]), FCString::Atoi(*Split[1])};
		Settings->SetScreenResolution(NewResoltuion);
		Settings->ApplySettings(false);

		if (Settings->GetFullscreenMode() == EWindowMode::Windowed)
		{
			GEngine->GameViewport->GetWindow()->Resize(NewResoltuion);
		}
	}
}

void UTPSOptionWidget::OnMasterVolumeChanged(float Value)
{
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = Value;
	}
}

void UTPSOptionWidget::OnBackButtonClicked()
{
	ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CloseOption();
	}
}
