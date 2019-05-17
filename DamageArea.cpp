// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageArea.h"


// Sets default values
ADamageArea::ADamageArea(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	RootComponent = ProxBox;
	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &ADamageArea::Prox);

	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(ProxBox);

	Damage = 100;
}

// Called when the game starts or when spawned
void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageArea::Prox_Implementation(class UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		// don't collide w/ anything other than the actor's root component
		return;
	}
	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);
}
