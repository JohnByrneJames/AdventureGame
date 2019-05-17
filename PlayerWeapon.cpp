// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "PlayerActor.h"
#include "Enemy.h"
#include "Engine.h"
#include "Engine/World.h"


// Sets default values
APlayerWeapon::APlayerWeapon(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxCapsule = PCIP.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("ProxCapsule"));
	RootComponent = ProxCapsule;
	ProxCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerWeapon::Prox);

	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(ProxCapsule);

	Damage = 1;
}

void APlayerWeapon::Prox_Implementation(class UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		// don't collide with anything other than the actors root component
		return;
	}

	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);

}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




