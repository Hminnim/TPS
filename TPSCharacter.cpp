// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "TPSWeapon.h"
#include "TPSGameMode.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set Default
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Create Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set Default Camera
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = DefaultSpringArmLength;
	SpringArm->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	EquipWeapon();
	OnTakeAnyDamage.AddDynamic(this, &ATPSCharacter::OnTakeDamage);
	GameMode->SetHealthBar(MaxHealthPoint, CurrentHealthPoint);
}

void ATPSCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATPSCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isDeath) return;

	SetAimCamera(DeltaSeconds);
	HandleFootstep(DeltaSeconds);
	HandleFallingDeath(DeltaSeconds);
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding Input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Sprint);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Look);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Aim);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Shoot);
		EnhancedInputComponent->BindAction(ReloadtAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Reload);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ATPSCharacter::GamePause);
	}
}

void ATPSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YaRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YaRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YaRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementValue.Y);
	AddMovementInput(RightDirection, MovementValue.X);
}

void ATPSCharacter::Sprint(const FInputActionValue& Value)
{
	if (isAim || isReload) return;

	isSprint = Value.Get<bool>();
	if (isSprint)
		GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	else
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ATPSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(-LookValue.Y);
}

void ATPSCharacter::Aim(const FInputActionValue& Value)
{
	isAim = Value.Get<bool>();

	if (isAim) GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	if (!isAim) CurWeapon->StopFire();

	GetCharacterMovement()->bOrientRotationToMovement = !isAim;
	GameMode->UpdateCrosshair(isAim);
}

void ATPSCharacter::SetAimCamera(float DeltaSeconds)
{
	if (isAim)
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = GetControlRotation();

		float InterpSpeed = 10.0f;

		FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, InterpSpeed);

		SetActorRotation(SmoothRotation);

		float ZoomSpeed = 10.0f;

		SpringArm->TargetArmLength -= ZoomSpeed;
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, AimSpringArmLength, DefaultSpringArmLength);


		FVector NewLocation = FMath::Lerp(AimCameraLocation, DefaultCameraLocation, 0.1f);
		Camera->SetRelativeLocation(NewLocation);
	}
	else if (!isAim)
	{
		float ZoomSpeed = 10.0f;

		SpringArm->TargetArmLength += ZoomSpeed;
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, AimSpringArmLength, DefaultSpringArmLength);

		FVector NewLocation = FMath::Lerp(DefaultCameraLocation, AimCameraLocation, 0.1f);
		Camera->SetRelativeLocation(NewLocation);
	}

	if (CurWeapon->CurrentAmmo <= 0) isShoot = false;
}

void ATPSCharacter::Shoot(const FInputActionValue& Value)
{
	if (!isAim) return;
	if (isReload) return;

	isShoot = Value.Get<bool>();
	if (isShoot)
	{
		CurWeapon->StartFire(Camera);
	}
	else
	{
		CurWeapon->StopFire();
	}
}

void ATPSCharacter::EquipWeapon()
{
	FName WeaponSocket(TEXT("hand_rSocket"));
	CurWeapon = GetWorld()->SpawnActor<ATPSWeapon>(Weapon, FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon) {
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			CurWeapon->SetController(PlayerController);
		}
		
		if (GameMode)
		{
			GameMode->SetAmmo(CurWeapon->CurrentAmmo, CurWeapon->MaxAmmo);
		}
	}
}

void ATPSCharacter::Reload()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (isReload) return;

	CurWeapon->StopFire();
	isShoot = false;
	isReload = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, FTimerDelegate::CreateLambda([&]() {
		CurWeapon->Reload();
		isReload = false;
		if (reloadSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, reloadSound, GetActorLocation());
		}
		}), CurWeapon->ReloadTime, false);
}

void ATPSCharacter::GamePause()
{
	GameMode->GamePause();
}

void ATPSCharacter::HandleFootstep(float DeltaSeconds)
{
	if (!walkSound) return;
	if (GetCharacterMovement()->IsFalling()) return;
	if (!GetCharacterMovement()->IsMovingOnGround()) return;

	float CharacterSpeed = GetVelocity().Size2D();
	float FootstepInterval = CharacterSpeed >= 1000.0f ? 0.25f : 0.5f;

	FootstepTimer += DeltaSeconds;
	if (CharacterSpeed > 0.0f)
	{
		if (FootstepTimer > FootstepInterval)
		{
			FootstepTimer = 0.0f;
			UGameplayStatics::PlaySoundAtLocation(this, walkSound, GetActorLocation());
		}
	}
	else
	{
		FootstepTimer = 0.0f;
	}
	
}

void ATPSCharacter::HandleFallingDeath(float DeltaSeconds)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		FallingTimer = 0.0f;
		return;
	}

	float FallingDeathTime = 5.0f;

	FallingTimer += DeltaSeconds;
	if (FallingTimer >= FallingDeathTime)
	{
		UpdateHealthPoint(-100.0f);
	}
}

void ATPSCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ATPSCharacter::UpdateHealthPoint(-Damage);
	GameMode->SetHealthBar(MaxHealthPoint, CurrentHealthPoint);
}

bool ATPSCharacter::GetAim()
{
	return isAim;
}

bool ATPSCharacter::GetShoot()
{
	return isShoot;
}

bool ATPSCharacter::GetReload()
{
	return isReload;
}

void ATPSCharacter::UpdateHealthPoint(float amount)
{
	CurrentHealthPoint += amount;
	if (CurrentHealthPoint <= 0)
	{
		isDeath = true;
		GameMode->GameOver();
	}
}
