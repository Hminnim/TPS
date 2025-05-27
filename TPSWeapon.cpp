// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSWeapon.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "TPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TPSMonster.h"

// Sets default values
ATPSWeapon::ATPSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	RootComponent = WeaponMesh;
	WeaponMesh->SetCollisionProfileName("NoCollision");

	
}

// Called when the game starts or when spawned
void ATPSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPSWeapon::SetController(APlayerController* CharacterController)
{
	PlayerController = CharacterController;
}

void ATPSWeapon::Fire(TWeakObjectPtr<UCameraComponent> camera)
{
	if (CurrentAmmo <= 0)
	{
		StopFire();
		return;
	}

	auto Camera = camera.Get();

	FireStart = Camera->GetComponentLocation() + Camera->GetForwardVector() * 150;
	FireEnd = (Camera->GetForwardVector() * 10000) + FireStart;
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, FireStart, FireEnd, ECollisionChannel::ECC_Visibility))
	{
		if (HitResult.GetActor())
		{
			Attack(HitResult.GetActor());
			if (ATPSMonster* HitMonster = Cast<ATPSMonster>(HitResult.GetActor()))
			{
				HitMonster->UpdateHealthPoint(-Damage);
			}
		}
	}

	ApplyRecoil();
	CurrentAmmo--;
	ATPSGameMode* GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->UpdateAmmo(CurrentAmmo);
	}
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ATPSWeapon::Attack(AActor* TargetMonster)
{
	UGameplayStatics::ApplyDamage(TargetMonster, Damage, PlayerController, this, UDamageType::StaticClass());
}

void ATPSWeapon::StartFire(TWeakObjectPtr<UCameraComponent> camera)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastFireTime < FireRate) return;

	Fire(camera);
	LastFireTime = CurrentTime;
	if(isAuto)
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [camera, this]() {Fire(camera); }, FireRate, true);
}

void ATPSWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ATPSWeapon::Reload()
{
	CurrentAmmo = MaxAmmo;
	ATPSGameMode* GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->UpdateAmmo(CurrentAmmo);
	}
}

void ATPSWeapon::ApplyRecoil()
{
	float YawRecoil = FMath::RandRange(-YawRecoilAmount, YawRecoilAmount);

	PlayerController->AddPitchInput(-PitchRecoilAmount);
	PlayerController->AddYawInput(YawRecoil);
}

