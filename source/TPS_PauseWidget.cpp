// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TPSGameMode.h"

bool UTPS_PauseWidget::Initialize()
{
	Super::Initialize();

	// Widget bind
	if (OptionButton)
	{
		OptionButton->OnClicked.AddDynamic(this, &UTPS_PauseWidget::OnOptionButtonClicked);
	}
	if (TitleButton)
	{
		TitleButton->OnClicked.AddDynamic(this, &UTPS_PauseWidget::OnTitleButtonClicked);
	}
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UTPS_PauseWidget::OnBackButtonClicked);
	}

	return true;
}

// Open option widget
void UTPS_PauseWidget::OnOptionButtonClicked()
{
	ATPSGameMode* GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OpenOption();
	}
}

// Go to title menu
void UTPS_PauseWidget::OnTitleButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "Title");
}

// Close pause widget
void UTPS_PauseWidget::OnBackButtonClicked()
{
	ATPSGameMode* GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GameResume();
	}
}
