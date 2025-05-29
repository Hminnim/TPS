// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSTitleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "TPSTitleMenuWidget.h"
#include "Kismet/GameplayStatics.h"

ATPSTitleGameMode::ATPSTitleGameMode()
{
}

void ATPSTitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GameWidgetClass)
	{
		GameWidget = Cast<UTPSTitleMenuWidget>(CreateWidget(GetWorld(), GameWidgetClass));
	}

	if (GameWidget)
	{
		GameWidget->AddToViewport();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->SetShowMouseCursor(true);
			PlayerController->SetInputMode(FInputModeUIOnly());
		}
	}
}
