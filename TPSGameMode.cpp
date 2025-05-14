// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameMode.h"
#include "TPSUserWidget.h"
#include "TPSGameOverWidget.h"
#include "TPSMonsterSpawner.h"
#include "TPS_PauseWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void ATPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetWidget();
	StartMonsterSpawn();
	StartTImer();
}

void ATPSGameMode::UpdateAmmoText()
{
	GameWidget->SetAmmoText(CurrentAmmo, MaxAmmo);
}

void ATPSGameMode::SetWidget()
{
	if (GameWidgetClass)
	{
		GameWidget = Cast<UTPSUserWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport(0);
			GameWidget->ShowCrosshair(false);
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				PC->SetShowMouseCursor(false);
				PC->SetInputMode(FInputModeGameOnly());
			}
		}
	}
}

void ATPSGameMode::SetAmmo(int32 currentAmmo, int32 maxAmmo)
{
	CurrentAmmo = currentAmmo;
	MaxAmmo = maxAmmo;
	UpdateAmmoText();
}

void ATPSGameMode::UpdateAmmo(int32 AmmoChange)
{
	CurrentAmmo = AmmoChange;
	UpdateAmmoText();
}

void ATPSGameMode::UpdateCrosshair(bool isShow)
{
	GameWidget->ShowCrosshair(isShow);
}

void ATPSGameMode::UpdateScore(int32 scoreChange)
{
	CurrentScore += scoreChange;
	GameWidget->SetScoreText(CurrentScore);
}

void ATPSGameMode::UpdateTimer()
{
	GameWidget->SetTimerText(CurrentTime);
	if (CurrentTime <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		GameOver();
	}
	else
	{
		CurrentTime--;
	}
}

void ATPSGameMode::StartTImer()
{
	CurrentTime = 120;

	GetWorld()->GetTimerManager().SetTimer
	(
		timerHandle,
		this,
		&ATPSGameMode::UpdateTimer,
		1.0f,
		true,
		0.0f
	);
}

void ATPSGameMode::StartMonsterSpawn()
{
	if (MonsterSpawnerClass && MonsterSpawner == nullptr)
	{
		MonsterSpawner = GetWorld()->SpawnActor<ATPSMonsterSpawner>(MonsterSpawnerClass);
	}
	if (MonsterSpawner)
	{
		MonsterSpawner->StartSpawning();
	}
}

void ATPSGameMode::GameOver()
{
	if (GameoverWidgetClass && GameoverWidget == nullptr)
	{
		GameoverWidget = Cast<UTPSGameOverWidget>(CreateWidget(GetWorld(), GameoverWidgetClass));
	}
	if (GameoverWidget)
	{
		GameoverWidget->AddToViewport(10);

	}
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetShowMouseCursor(true);
		PC->SetInputMode(FInputModeUIOnly());
	}
	GetWorldSettings()->SetTimeDilation(0.f);
	
}

void ATPSGameMode::GamePause()
{
	if (PauseWidgetClass && PauseWidget == nullptr)
	{
		PauseWidget = Cast<UTPS_PauseWidget>(CreateWidget(GetWorld(), PauseWidgetClass));
	}
	if (PauseWidget)
	{
		PauseWidget->AddToViewport(11);
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetShowMouseCursor(true);
		PC->SetInputMode(FInputModeUIOnly());
	}
	GetWorldSettings()->SetTimeDilation(0.f);
}

void ATPSGameMode::GameResume()
{
	if (PauseWidget)
	{
		PauseWidget->RemoveFromParent();
	}
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
	GetWorldSettings()->SetTimeDilation(1.f);
}
