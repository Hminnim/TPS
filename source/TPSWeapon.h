// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "TPSWeapon.generated.h"

class UCameraComponent;
class USoundBase;

UCLASS()
class TPS_API ATPSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSWeapon();

protected:
	// Values for fire handle
	FTimerHandle TimerHandle;
	float LastFireTime = -1.0f;
	FVector FireStart;
	FVector FireEnd;
	FVector FireDirection;

public:	
	// Weapon value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsAuto = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float CurrentAmmo = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float AttackRange = 10000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float MaxAmmo = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float ReloadTime = 2.2f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float PitchRecoilAmount = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float YawRecoilAmount = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	USoundBase* FireSound;

	// Player Component
	APlayerController* PlayerController;
	UCameraComponent* PlayerCamera;
	void SetPlayerComponent(APlayerController* CharacterController, UCameraComponent* CharacterCamera);

	// Weapon Function
	void Fire();
	void StartFire();
	void StopFire();
	void Reload();
	void ApplyRecoil();
};
