// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakableCrate.h"
#include "Engine.h"
#include "PickupItem.h"


// Sets default values
ABreakableCrate::ABreakableCrate(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	RootComponent = ProxBox;

	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(ProxBox);

	Explosion = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Explosion"));
	Explosion->AttachTo(ProxBox);

	HitPoints = 10.f;
}

// Called when the game starts or when spawned
void ABreakableCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABreakableCrate::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	HitPoints -= Damage;
	
	Explosion->ToggleActive();

	if (HitPoints <= 0)
	{
		HitPoints = 0;
		GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, "Crate Destroyed");
		
		lootDrop();	

		Destroy(Mesh);
	}

	

	return Damage;
}

void ABreakableCrate::lootDrop()
{
	FVector up = GetActorUpVector();
	FVector nozzle = ProxBox->GetComponentLocation();

	nozzle += up;

	//nozzle.Normalize();

	APickupItem* pickup = GetWorld()->SpawnActor<APickupItem>(BPLoot, nozzle,
		RootComponent->GetComponentRotation());		

	return;
}


