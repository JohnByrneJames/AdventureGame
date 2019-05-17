// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatforms.h"


// Sets default values
AMovingPlatforms::AMovingPlatforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PlatformSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));

}

// Called when the game starts or when spawned
void AMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingPlatforms::TogglePlatform()
{
	isActivatable = false; // Activate platforms turned off
}

// Called every frame
void AMovingPlatforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isActivatable)
	{

		FVector ActorLocation = GetActorLocation();

		ActorLocation.Y += speedOfPlatform;

		if (isDiagonal == true)
		{
			ActorLocation.Z += speedOfPlatform;
		}

		SetActorLocation(ActorLocation);

		if (ActorLocation.Y >= firstEnd) // 600 and above
		{
			speedOfPlatform *= -1.f;
			// UE_LOG(LogTemp, Warning, TEXT("600 >"));
		}

		if (ActorLocation.Y <= secondEnd) // 400 and below
		{
			speedOfPlatform *= -1.f;
			// UE_LOG(LogTemp, Warning, TEXT("400 <"));
		}
	}
	else if (isActivatable && Activated == true)
	{
		FVector ActorLocation = GetActorLocation();

		ActorLocation.Y += speedOfPlatform;

		SetActorLocation(ActorLocation);

		if (ActorLocation.Y >= firstEnd) // 600 and above
		{
			speedOfPlatform *= -1.f;
			// UE_LOG(LogTemp, Warning, TEXT("600 >"));
		}

		if (ActorLocation.Y <= secondEnd) // 400 and below
		{
			speedOfPlatform *= -1.f;
			// UE_LOG(LogTemp, Warning, TEXT("400 <"));
		}
	}

}
