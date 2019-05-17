// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "PickupItem.h"
#include "PlayerActor.generated.h"

//class UInputComponent;
//class UTimelineComponent;

UCLASS()
class ADVENGAME_API APlayerActor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerActor();

	// Enable Character to pick up Items
	void Pickup(APickupItem *item); 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called Every frame
	virtual void Tick(float DeltaTime) override;


	//New member function declarations
	//These will be used to move the player around
	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) 
																		override; // Override the default SetupPlayerInputController
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Yaw(float amount);
	void Pitch(float amount);
	void OnAction(); // On interaction with Lever/ Switch
	void OnAttack();

	UPROPERTY(BlueprintReadOnly, Category = "Is the Character walking")
		bool bisWalking;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UCapsuleComponent* TriggerCapsule;
	
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		class ASwitchLever* CurrentLightSwitch;	

		class AMovingPlatforms* PlatformActivation;

		class ADoorAccessable* DoorActivation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
			AActor* targetActor;

		// Healthbar - Current HP [Help adjust the size of the healthbar on screen]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		float Hp;
		// Healthbar - Max HP [Full health bar amount EG. 100] Make sure is available to the HUD class too
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		float MaxHp;

		// Attack Code
	UPROPERTY(BlueprintReadWrite, Category = AnimationState)
		bool AttackStarted;

	UPROPERTY(BlueprintReadWrite, Category = AnimationState)
		bool dead;

	// The bullet class theme enemy uses. If this is not set, it uses a melee attack
	// Connect the bullet blueprint to the enemy blueprint via the blueprint editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		UClass* BPFireball;

	// Force to be applied to projectile
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = EnemyProperties)
		float BulletLaunchImpulse;

	// Control cooldown between attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float AttackTimeout;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float TimeSinceLastStrike;

	// Can the player attack
		bool canAttack;

	// Does the player have the door key?
		bool hasKey;

		void keyCaptured();

	// Knockback Effect on player
	FVector Knockback;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	// Timer decleartions, did not work properly due to Unreal Engine Error so I
	// Left them here and in the cpp for reference.
	// UFUNCTION()
	//	void RepeatingFunction();

	// UPROPERTY(BlueprintReadWrite, Category = "Restart Delay")
	// 	float respawnDelay;

	//Timers [Used to add a delay between the death and respawn]
	// struct FTimerHandle MemberTimerHandle;

	// The Avatars Backpack AKA inventory and Icons
	int count;
	TMap<FString, int> Backpack; 
	TMap<FString, UTexture2D*> Icons;
	TMap<FString, UClass*> Classes;

	// Run When the player wants to see Inventory [Toggle]
	bool inventoryShowing;
	void ToggleInventory();
};
