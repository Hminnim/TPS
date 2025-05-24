// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSMonster.h"
#include "TPSGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include <Perception/AISense_Damage.h>

// Sets default values
ATPSMonster::ATPSMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Set Collision
	GetMesh()->SetCollisionProfileName("BlockAll");
}

// Called when the game starts or when spawned
void ATPSMonster::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &ATPSMonster::OnTakeDamage);

}

// Called every frame
void ATPSMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPSMonster::UpdateHealthPoint(float amount)
{
	HealthPoint += amount;
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
