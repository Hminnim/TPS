// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSMonster.h"
#include "TPSGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "TPSHealthBar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <Perception/AISense_Damage.h>

// Sets default values
ATPSMonster::ATPSMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set Collision
	GetMesh()->SetCollisionProfileName("BlockAll");

	if (!HealthBar)
	{
		HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
		HealthBar->SetupAttachment(GetMesh());
		HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
		HealthBar->SetWidgetSpace(EWidgetSpace::World);
		HealthBar->SetDrawSize(FVector2D(220.0f, 20.0f));
		HealthBar->SetPivot(FVector2D(0.5f, 0.5f));

		static ConstructorHelpers::FClassFinder<UTPSHealthBar> WidgetClass(TEXT("/Game/Games/GameMode/UI/WBP_HealthBar.WBP_HealthBar_C"));
		if(WidgetClass.Succeeded())
		{
			HealthBar->SetWidgetClass(WidgetClass.Class);
		}
	}
}

// Called when the game starts or when spawned
void ATPSMonster::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &ATPSMonster::OnTakeDamage);
	HealthBarWidget = Cast<UTPSHealthBar>(HealthBar->GetUserWidgetObject());
	if(HealthBarWidget)
	{
		HealthBarWidget->SetHPBar(HealthPoint, MaxHealthPoint);
	}
}

// Called every frame
void ATPSMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthBar)
	{
		FVector HPLocation = HealthBar->GetComponentLocation();
		FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(HPLocation, CameraLocation);
		HealthBar->SetWorldRotation(LookAtRotation);
	}
}

void ATPSMonster::UpdateHealthPoint(float amount)
{
	HealthPoint += amount;
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHPBar(HealthPoint, MaxHealthPoint);
	}
	if (HealthPoint <= 0.0f) DestroyMonster();

}

void ATPSMonster::DestroyMonster()
{
	// Update Score
	ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->UpdateScore(1);
	}

	// Change Collision
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);

}

void ATPSMonster::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!InstigatedBy->IsPlayerController()) return;

	if (HitSound)
	{
		UGameplayStatics::PlaySound2D(this, HitSound);
	}

	UAISense_Damage::ReportDamageEvent
	(
		GetWorld(),
		this,
		DamageCauser,
		Damage,
		DamageCauser->GetActorLocation(),
		GetActorLocation()
	);
}
