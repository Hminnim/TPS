// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <EnhancedInputLibrary.h>
#include "TPSCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USkeletalMeshComponent;
class ATPSWeapon;
class ATPSGameMode;
class USoundBase;


UCLASS()
class TPS_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyControllerChanged() override;
	virtual void Tick(float DeltaSeconds);

	// VALUE //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthPoint")
	float MaxHealthPoint = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthPoint")
	float CurrentHealthPoint = 100.0f;

	// Sounds //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Sounds")
	USoundBase* walkSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Sounds")
	USoundBase* reloadSound;

	// GET VALUE //
	bool GetAim();
	bool GetShoot();
	bool GetReload();

	// FUNCTION //
	void UpdateHealthPoint(float amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Define Compoents //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ATPSWeapon> Weapon;
	ATPSWeapon* CurWeapon;
	ATPSGameMode* GameMode;
	
	bool isSprint = false;
	bool isAim = false;
	bool isShoot = false;
	bool isReload = false;
	bool isDeath = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aim Setting")
	float DefaultSpringArmLength = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aim Setting")
	float AimSpringArmLength = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aim Setting")
	FVector DefaultCameraLocation = { 0.0f,0.0f,0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aim Setting")
	FVector AimCameraLocation = { 0.0f,40.0f,20.0f };

	FTimerHandle ReloadTimer;
	float FootstepTimer = 0.0f;
	float FallingTimer = 0.0f;

private:

	// INPUT //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* ReloadtAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"));
	UInputAction* PauseAction;

	// FUNCTION //
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
	void SetAimCamera(float DeltaSeconds);
	void Shoot(const FInputActionValue& Value);
	void EquipWeapon();
	void Reload();
	void GamePause();
	void HandleFootstep(float DeltaSeconds);
	void HandleFallingDeath(float DeltaSeconds);
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
