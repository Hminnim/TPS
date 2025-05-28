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
	
	// Set default character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Create components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Sets default camera
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
	GameMode->SetHealthBar(MaxHealthPoint, CurrentHealthPoint);
	
	EquipWeapon();
	
	OnTakeAnyDamage.AddDynamic(this, &ATPSCharacter::OnTakeDamage);
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

	if (bIsDeath)
	{
		return;
	}

	SetAimCamera(DeltaSeconds);
	HandleFootstep(DeltaSeconds);
	HandleFallingDeath(DeltaSeconds);
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding Action Input
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
	if (bIsAim || bIsReload)
	{
		return;
	}

	bIsSprint = Value.Get<bool>();
	if (bIsSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void ATPSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(-LookValue.Y);
}

void ATPSCharacter::Aim(const FInputActionValue& Value)
{
	bIsAim = Value.Get<bool>();

	if (bIsAim)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	if (!bIsAim)
	{
		CurrentWeapon->StopFire();
	}

	GetCharacterMovement()->bOrientRotationToMovement = !bIsAim;
	GameMode->UpdateCrosshair(bIsAim);
}

void ATPSCharacter::SetAimCamera(float DeltaSeconds)
{
	if (bIsAim)
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
	else if (!bIsAim)
	{
		float ZoomSpeed = 10.0f;

		SpringArm->TargetArmLength += ZoomSpeed;
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, AimSpringArmLength, DefaultSpringArmLength);

		FVector NewLocation = FMath::Lerp(DefaultCameraLocation, AimCameraLocation, 0.1f);
		Camera->SetRelativeLocation(NewLocation);
	}

	if (CurrentWeapon->CurrentAmmo <= 0)
	{
		bIsShoot = false;
	}
}

void ATPSCharacter::Shoot(const FInputActionValue& Value)
{
	if (!bIsAim || bIsReload)
	{
		return;
	}

	bIsShoot = Value.Get<bool>();
	if (bIsShoot)
	{
		CurrentWeapon->StartFire(Camera);
	}
	else
	{
		CurrentWeapon->StopFire();
	}
}

void ATPSCharacter::EquipWeapon()
{
	FName WeaponSocket(TEXT("hand_rSocket"));
	CurrentWeapon = GetWorld()->SpawnActor<ATPSWeapon>(Weapon, FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurrentWeapon) {
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			CurrentWeapon->SetController(PlayerController);
		}
		
		if (GameMode)
		{
			GameMode->SetAmmo(CurrentWeapon->CurrentAmmo, CurrentWeapon->MaxAmmo);
		}
	}
}

void ATPSCharacter::Reload()
{
	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}
	if (bIsReload)
	{
		return;
	}

	CurrentWeapon->StopFire();
	bIsShoot = false;
	bIsReload = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	GetWorld()->GetTimerManager().SetTimer
	(
		ReloadTimer, 
		FTimerDelegate::CreateLambda
		([&]() 
			{
				CurrentWeapon->Reload();
				bIsReload = false;
				if (ReloadSound)
				{
				UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
				}
			}
		), 
		CurrentWeapon->ReloadTime,
		false
	);
}

void ATPSCharacter::GamePause()
{
	GameMode->GamePause();
}

void ATPSCharacter::HandleFootstep(float DeltaSeconds)
{
	if (!WalkSound)
	{
		return;
	}
	if (GetCharacterMovement()->IsFalling() || !GetCharacterMovement()->IsMovingOnGround())
	{
		return;
	}

	float CharacterSpeed = GetVelocity().Size2D();
	float FootstepInterval = CharacterSpeed >= 1000.0f ? 0.25f : 0.5f;

	FootstepTimer += DeltaSeconds;
	if (CharacterSpeed > 0.0f)
	{
		if (FootstepTimer > FootstepInterval)
		{
			FootstepTimer = 0.0f;
			UGameplayStatics::PlaySoundAtLocation(this, WalkSound, GetActorLocation());
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

bool ATPSCharacter::IsAiming() const
{
	return bIsAim;
}

bool ATPSCharacter::IsShooting() const
{
	return bIsShoot;
}

bool ATPSCharacter::IsRealoading() const
{
	return bIsReload;
}

void ATPSCharacter::UpdateHealthPoint(float Amount)
{
	CurrentHealthPoint += Amount;
	if (CurrentHealthPoint <= 0)
	{
		bIsDeath = true;
		GameMode->GameOver();
	}
}
