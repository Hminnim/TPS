// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UTPSGameOverWidget::Initialize()
{
	Super::Initialize();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UTPSGameOverWidget::OnRestartButtonClicked);
	}
	if (TitleButton)
	{
		TitleButton->OnClicked.AddDynamic(this, &UTPSGameOverWidget::OnTitleButtonClicked);
	}

	return true;
}

void UTPSGameOverWidget::OnRestartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "Main");
}

void UTPSGameOverWidget::OnTitleButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "Title");
}
