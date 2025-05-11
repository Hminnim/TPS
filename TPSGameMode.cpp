// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameMode.h"
#include "TPSUserWidget.h"
#include "TPSMonsterSpawner.h"
#include "Kismet/GameplayStatics.h"

void ATPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetWidget();
	StartMonsterSpawn();
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
			GameWidget->AddToViewport();
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

void ATPSGameMode::StartMonsterSpawn()
{
	if (MonsterSpawnerClass)
	{
		MonsterSpawner = GetWorld()->SpawnActor<ATPSMonsterSpawner>(MonsterSpawnerClass);

		if (MonsterSpawner)
		{
			MonsterSpawner->StartSpawning();
		}
	}
}