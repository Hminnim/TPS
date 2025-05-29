// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSWeapon.h"
#include "TimerManager.h"
#include "TPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TPSMonster.h"

// Sets default values
ATPSWeapon::ATPSWeapon()
{
	// Set WeaponMesh default values
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	RootComponent = WeaponMesh;
	WeaponMesh->SetCollisionProfileName("NoCollision");
}

void ATPSWeapon::SetPlayerComponent(APlayerController* CharacterController, UCameraComponent* CharacterCamera)
{
	PlayerController = CharacterController;
	PlayerCamera = CharacterCamera;
}

void ATPSWeapon::Fire()
{
	if (CurrentAmmo <= 0)
	{
		StopFire();
		return;
	}

	// Line trace
	FireStart = PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * 150;
	FireEnd = (PlayerCamera->GetForwardVector() * AttackRange) + FireStart;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, FireStart, FireEnd, ECollisionChannel::ECC_Visibility))
	{
		if (HitResult.GetActor())
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, PlayerController, this, UDamageType::StaticClass());
		}
	}

	ApplyRecoil();

	// Update widget ammo text
	CurrentAmmo--;
	ATPSGameMode* GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->UpdateAmmo(CurrentAmmo);
	}
	// Play fire sound
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ATPSWeapon::StartFire()
{
	// Fire rate
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastFireTime < FireRate)
	{
		return;
	}

	// If this weapon is auto, repeat fire function
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATPSWeapon::Fire, FireRate, bIsAuto, 0.0f);
	LastFireTime = CurrentTime;
}

void ATPSWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ATPSWeapon::Reload()
{
	CurrentAmmo = MaxAmmo;

	// Update widget ammo text
	ATPSGameMode* GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->UpdateAmmo(CurrentAmmo);
	}
}

// Apply recoil by moving camera randomly
void ATPSWeapon::ApplyRecoil()
{
	float YawRecoil = FMath::RandRange(-YawRecoilAmount, YawRecoilAmount);

	PlayerController->AddPitchInput(-PitchRecoilAmount);
	PlayerController->AddYawInput(YawRecoil);
}

