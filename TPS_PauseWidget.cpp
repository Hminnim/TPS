// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TPSGameMode.h"

bool UTPS_PauseWidget::Initialize()
{
	Super::Initialize();

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

void UTPS_PauseWidget::OnOptionButtonClicked()
{
	ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->OpenOption();
	}
}

void UTPS_PauseWidget::OnTitleButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "Title");
}

void UTPS_PauseWidget::OnBackButtonClicked()
{
	ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->GameResume();
	}
}
