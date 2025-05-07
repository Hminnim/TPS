// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSMonster.generated.h"

UCLASS()
class TPS_API ATPSMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSMonster();

	// Monster Value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster Value")
	float HealthPoint = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster Value")
	float AttackDamage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster Value")
	float AttackRange = 300.0f;

	bool isDead = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function
	void UpdateHealthPoint(float amount);
	virtual void DestroyMonster();
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
