// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"



UCLASS()
class ADVENGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy(const class FObjectInitializer& PCIP);

	// Enemy Speed Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float Speed;

	// Enemy health Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float HitPoints;

	// Enemy Experience Amount (EXP)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		int Experience;

	// Enemy drops (Weapons, Coins ECT)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass *BPLoot;

	// Enemy base Damage amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float BaseAttackDamage;

	// Enemy time between attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float AttackTimeout;

	// Enemy's time since last attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float TimeSinceLastStrike;

	// Enemy Range of Sight | Visualised as a sphere in editor
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* SightSphere;

	// Enemy Attack Range | Visualised as a sphere in editor
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* AttackRangeSphere;

	//inline functions to calculate immediately the distance 'd'
	bool isInAttackRange(float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}

	bool isInSightRange(float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}

	// Helps Animations play when enemey is attacking
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attacking?")
		bool bisAttacking;
	// Helps Animations play when enemy is dead
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attacking?")
		bool bisDead;


	// The bullet class theme enemy uses. If this is not set, it uses a melee attack
	// Connect the bullet blueprint to the enemy blueprint via the blueprint editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		UClass* BPBullet;

	// The amount of damage attacks do, gets added to weapon damage
	// The impulse will expose the variable for the force to be applied
	// to the bullet E.G how fast it fires/ travels
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = EnemyProperties)
		float BulletLaunchImpulse;

	// The attack method
	void Attack(AActor* thing);

	// Knockback Effect on player
	FVector Knockback;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
