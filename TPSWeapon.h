// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
	float LastFireTime = -1.0f;
	FVector FireStart;
	FVector FireEnd;
	FVector FireDirection;

	// Player Component
	APlayerController* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Weapon Value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool isAuto = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float CurrentAmmo = 30.0f;
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

	void SetController(APlayerController* CharacterController);

	// Weapon Function
	void Fire(TWeakObjectPtr<UCameraComponent> camera);
	void Attack(AActor* TargetMonster);
	void StartFire(TWeakObjectPtr<UCameraComponent> camera);
	void StopFire();
	void Reload();
	void ApplyRecoil();
};
