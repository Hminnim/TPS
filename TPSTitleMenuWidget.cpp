// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSTitleMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UTPSTitleMenuWidget::Initialize()
{
	Super::Initialize();
	
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTPSTitleMenuWidget::OnStartButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UTPSTitleMenuWidget::OnQuickButtonClicked);
	}

	return true;
}

void UTPSTitleMenuWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "Main");
}

void UTPSTitleMenuWidget::OnQuickButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
