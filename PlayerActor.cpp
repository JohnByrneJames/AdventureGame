// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerActor.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "SwitchLever.h"
#include "Enemy.h"
#include "Bullet.h"
#include "DoorAccessable.h"
#include "MyHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "MovingPlatforms.h"


// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialise Properties
	AttackTimeout = 1.5f; // Cooldown per attack
	TimeSinceLastStrike = 0; // Cooldown counter
	canAttack = true; // Can the player attack
	count = 0;

	// create trigger capsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);	

	// bind trigger events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerActor::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &APlayerActor::OnOverlapEnd);

	// set current light switch to null
	CurrentLightSwitch = nullptr;

	PlatformActivation = nullptr;

	// Set attacking boolean to false
	AttackStarted = false;

	// Retrieve Time manager for delay functionality
	// Get the world, get the timer manager, set a new timer with this handle 'TimerHandle' and set it to
	// 5 Seconds, after 5 seconds trigger this function 'onTimerEnd'.
	// GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &APlayerActor::RepeatingFunction, 2.0f, false, 5.0f);

	
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Apply knockback vector
	AddMovementInput(Knockback, 100.f);

	// half it each frame
	Knockback *= 0.5f;

	// Restart Game if player has died
	if (dead == true)
	{
		// Turns off player controller for the player;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerActor::DisableInput(PlayerController);

		// Restart game
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}


	// Cooldown between enemy attacks
	if (TimeSinceLastStrike <= 0 && canAttack) // returns null or 0
	{
		
		// If the cooldown is over, then attack again
		// this resets the hit parameter	
		UE_LOG(LogTemp, Warning, TEXT("Can attack is FALSE"));
	}

	TimeSinceLastStrike += DeltaTime;

	if (TimeSinceLastStrike > AttackTimeout && !canAttack)
	{
		canAttack = true;
		TimeSinceLastStrike = 0;	
		UE_LOG(LogTemp, Warning, TEXT("Can attack is TRUE"));
	}
}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(InputComponent);
	InputComponent->BindAxis("Forward", this, &APlayerActor::MoveForward);	
	InputComponent->BindAxis("Strafe", this, &APlayerActor::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Action", IE_Pressed, this, &APlayerActor::OnAction); // Interact with Items
	InputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerActor::ToggleInventory);
	InputComponent->BindAxis("Yaw", this, &APlayerActor::Yaw);
	InputComponent->BindAxis("Pitch", this, &APlayerActor::Pitch);

	// Attack Input
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerActor::OnAttack);
}

void APlayerActor::OnAttack()
{
	AttackStarted = true;

	// if canAttack is true the player can attack
	if (canAttack)
	{
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("ArmR3");

		nozzle += fwd * 55;

		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(BPFireball, nozzle,
			RootComponent->GetComponentRotation());

		canAttack = false;

		if (bullet)
		{
			bullet->Firer;
			bullet->ProxSphere->AddImpulse(fwd*BulletLaunchImpulse);
		}
	}
	

	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, "Attacked %s");
}

void APlayerActor::MoveForward(float amount)
{
	if (inventoryShowing)
	{
		// If the inventory is currently being displayed exit this method, consequenstally
		// disabling the players movement controls intialized after.
		return;
	}
	// Don't enter the body of this function if Controller is
	// not set up yet, or if the amount to move is equal to 0
	if (Controller && amount)
	{
		bisWalking = true;
		FVector fwd = GetActorForwardVector();		
		// we call AddMovementInput to actually move the player
		// by `amount` in the `fwd` direction
		AddMovementInput(fwd, amount);
	}

	if (amount <= 0)
	{
		bisWalking = false;
	}
	
}

void APlayerActor::MoveRight(float amount)
{
	if (inventoryShowing)
	{
		return;
	}

	if (Controller && amount)
	{		
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void APlayerActor::Yaw(float amount)
{
	if (inventoryShowing)
	{
		// if the button is down click drag
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}

	AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}
void APlayerActor::Pitch(float amount)
{
	if (inventoryShowing)
	{
		// if the button is down click drag
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}

	AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

void APlayerActor::OnAction()
{
	// Toggles when the LightSwitch isn't equal to note
	//if (CurrentLightSwitch)
	//{
	//	CurrentLightSwitch->ToggleLight();		
	//}
	//
	if (PlatformActivation)
	{
		UE_LOG(LogTemp, Warning, TEXT("IN FUNCTION"));
		PlatformActivation->TogglePlatform();
	}
}

// overlap on begin function
void APlayerActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/* If player overlaps with actor, check for that actors class then add a pointer to that class definition
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(ASwitchLever::StaticClass()))
	{
		CurrentLightSwitch = Cast<ASwitchLever>(OtherActor);
	}
	*/

	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(AMovingPlatforms::StaticClass()))
	{
		PlatformActivation = Cast<AMovingPlatforms>(OtherActor);
	}
}

// overlap on end function
void APlayerActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		CurrentLightSwitch = nullptr;
	}
	*/

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		PlatformActivation = nullptr;
	}
}

float APlayerActor::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Hp -= Damage;
	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, "Damage Taken");
	// Add some knockback that gets applied over a few frames
	Knockback = GetActorLocation() - DamageCauser->GetActorLocation();
	Knockback.Normalize();
	Knockback *= Damage * 1000;

	// If the player goes below 0 hp, he will die
	if (Hp <= 0)
	{
		Hp = 0; // clamp
		//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, "Game Over");

		// Player is dead
		dead = true;
	}
	return Damage;
}

void APlayerActor::Pickup(APickupItem *item)
{
	// This will add items to the players backup of type 'APickupItem'
	// If the player already has that item, the code increases the quanity,
	// however if they do not have that item it will add the new item with a 
	// name, quanity and icon
	if (Backpack.Contains(item->Name))
	{
		Backpack[item->Name] += item->Quantity;
	}
	else
	{
		Backpack.Add(item->Name, item->Quantity);
		Icons.Add(item->Name, item->Icon);
	}
}

void APlayerActor::ToggleInventory()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	if (inventoryShowing)
	{
		hud->clearWidgets();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}
	else
	{
		inventoryShowing = true;
		PController->bShowMouseCursor = true;
		for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
		{
			//Combine string name of the item, with qty eg Cow x 5
			FString fs = it->Key + FString::Printf(TEXT("x%d"), it->Value);

			//GEngine->AddOnScreenDebugMessage(count++, 30.f, FColor::Red, fs).
			UTexture2D* tex;

			if (Icons.Find(it->Key))
			{
				tex = Icons[it->Key];
				Widget w(Icon(fs, tex), fs);
				hud->addWidget(w);
			}
		}
	}
}

void APlayerActor::keyCaptured()
{
	//AActor *player = Cast<ADoorAccessable>(OtherActor);

	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Orange, "Key Captured");
}

/*
void APlayerActor::RepeatingFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello Timer"));
}
*/





