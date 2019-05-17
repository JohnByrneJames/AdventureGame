// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PlayerActor.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.h"
#include "Engine/World.h"
#include "MyHUD.h"
#include "Engine.h"


// Sets default values
AEnemy::AEnemy(const class FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this character to call Tick() every frame.  
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialise Properties of Enemy
	Speed = 20;
	HitPoints = 20;
	Experience = 0;
	BPLoot = NULL;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;

	SightSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
	SightSphere->SetupAttachment(RootComponent);

	AttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move towards the player every frame
	APlayerActor* avatar = Cast<APlayerActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;

	// Locate the players location and create a variable that will move towards
	// that location. Assign that variable to a movement input with the speed at which
	// the enemy will move each frame.

	FVector playerPos = avatar->GetActorLocation();
	FVector toPlayer = playerPos - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();
	
	// If the player is not in the SightSphere of the monster, then go back
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		// stop Attack animation
		bisAttacking = false;

		// If the player is out of sight then enemy cannot chase
		return;
	}
	// Stop Attack Animation
	
	
	// normalizes the vector
	toPlayer /= distanceToPlayer;
	

	// This adds movement towards the player continuously
	//AddMovementInput(toPlayer, Speed * DeltaTime);

	// At least face the target
	// Gets you the rotator to turn something
	// that looks in the 'toPlayer' direction.
	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0; // 0 off the pitch

	if (!bisDead)
	{
		RootComponent->SetWorldRotation(toPlayerRotation);
	}
	
	// Attack code
	if (isInAttackRange(distanceToPlayer) && !bisDead)
	{
		
		// Perform the attack.
		if (!TimeSinceLastStrike)
		{
			
			// If the cooldown is over, then attack again
			// this resets the hit parameter.
			Attack(avatar);
		}

		TimeSinceLastStrike += DeltaTime;

		if (TimeSinceLastStrike > AttackTimeout)
		{
			
			TimeSinceLastStrike = 0;
		}
		
		return; // Do nothing else
	}

	// Knockback 
	AddMovementInput(Knockback, 1.f);
	Knockback *= 0.5f;
}

void AEnemy::Attack(AActor* thing)
{
	
	if (BPBullet)
	{
		// Start attack animation
		bisAttacking = true;
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("Neck1");

		// Move it forward 'fwd' of the enemy so it doesn't collide with 
		// the enemies model. 
		nozzle += fwd * 55;

		FVector toOpponent = thing->GetActorLocation() - nozzle;
		toOpponent.Normalize();
		// This is used to spawn a new actor into the level, in this case
		// a bullet prefab.
		ABullet *bullet = GetWorld()->SpawnActor<ABullet>(BPBullet, nozzle,
			RootComponent->GetComponentRotation());

		// Checks whether the bullet BP holds a mesh, if it is true the impulse is added
		// to the bullet and the enemy will fire. Otherwise it will give an error.
		if (bullet)
		{			
			// Here we use the 'AddImpulse' method to add force to the bullet, this will
			// attack when the player is in AttackRange			
			bullet->Firer = this;
			bullet->ProxSphere->AddImpulse(fwd*BulletLaunchImpulse);
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, "monster: Bullet Spawned");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow,
				"monster: no bullet actor could be spawned. is the bullet overlapping something?");
		}
	}
}

float AEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	HitPoints -= Damage;

	Knockback = GetActorLocation() - DamageCauser->GetActorLocation();
	Knockback.Normalize();
	Knockback *= Damage * 500;

	if (HitPoints <= 0)
	{
		APlayerController *PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->addScore(Experience);

		HitPoints = 0;
		GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, "This Enemy is Dead");
		bisDead = true;
	}

	return Damage;
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

