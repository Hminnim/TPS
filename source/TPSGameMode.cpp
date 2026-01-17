// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameMode.h"
#include "TPSUserWidget.h"
#include "TPSGameOverWidget.h"
#include "TPSMonsterSpawner.h"
#include "TPS_PauseWidget.h"
#include "TPSOptionWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void ATPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetWidget();
	StartMonsterSpawn();
	StartTImer();
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

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				PlayerController->SetShowMouseCursor(false);
				PlayerController->SetInputMode(FInputModeGameOnly());
			}
		}
	}
}

void ATPSGameMode::UpdateAmmo(int32 CurrentAmmo, int32 MaxAmmo)
{
	GameWidget->SetAmmoText(CurrentAmmo, MaxAmmo);
}

void ATPSGameMode::UpdateCrosshair(bool bIsShow)
{
	GameWidget->ShowCrosshair(bIsShow);
}

void ATPSGameMode::UpdateScore(int32 Amount)
{
	CurrentScore += Amount;
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
	// Open Gameover widget
	if (GameoverWidgetClass && GameoverWidget == nullptr)
	{
		GameoverWidget = Cast<UTPSGameOverWidget>(CreateWidget(GetWorld(), GameoverWidgetClass));
	}
	if (GameoverWidget)
	{
		GameoverWidget->AddToViewport(10);

	}

	// Change input mode to UI only
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
	GetWorldSettings()->SetTimeDilation(0.0f);
}

void ATPSGameMode::GamePause()
{
	// Open Gamepause widget
	if (PauseWidgetClass && PauseWidget == nullptr)
	{
		PauseWidget = Cast<UTPS_PauseWidget>(CreateWidget(GetWorld(), PauseWidgetClass));
	}
	if (PauseWidget)
	{
		PauseWidget->AddToViewport(11);
	}

	// Change input mode to UI only
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
	GetWorldSettings()->SetTimeDilation(0.f);
}

void ATPSGameMode::GameResume()
{
	// Close Gamepause widget
	if (PauseWidget)
	{
		PauseWidget->RemoveFromParent();
	}

	// Change input mode to Game only
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
	GetWorldSettings()->SetTimeDilation(1.f);
}

void ATPSGameMode::OpenOption()
{
	if (OptionWidgetClass && OptionWidget == nullptr)
	{
		OptionWidget = Cast<UTPSOptionWidget>(CreateWidget(GetWorld(), OptionWidgetClass));
	}
	if (OptionWidget)
	{
		OptionWidget->AddToViewport(12);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OptionWidget Added"));
	}
}

void ATPSGameMode::CloseOption()
{
	if (OptionWidget)
	{
		OptionWidget->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Close")));
	}
}

void ATPSGameMode::SetHealthBar(float MaxHealth, float CurrentHealth)
{
	GameWidget->SetHealthBar(MaxHealth, CurrentHealth);
}
