// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "PlayerActor.h"
#include "Engine.h"
#include "Engine/World.h"

// Sets default values
ABullet::ABullet(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The bullet will simulate physics using its bounding sphere
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	RootComponent = ProxSphere;
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::Prox);

	// For the bullet, the mesh is "dumb". It just tags along with whatever
	// the ProxSphere is doing, since the ProxSphere is going to respond to collisions
	// with objects. Attach the Mesh to the ProxSphere.
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(ProxSphere);

	Damage = 50;

	//SetLifeSpan(2);

}

void ABullet::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		// don't collide with anything other than the actors root component
		return;
	}

	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, "Inside Prox_implementation in bullet");
	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);

	Destroy();
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

