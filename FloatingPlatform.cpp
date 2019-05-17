// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingPlatform.h"


// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// FTransform ActorTransform = GetTransform();
	// FVector Location = ActorTransform.GetLocation();

	//FVector ActorLocation = FVector(10.f, 20.f, 30.f);
	//SetActorLocation(ActorLocation);

	// ActorTransform.GetTranslation();
	// ActorTransform.GetRotation();
	// ActorTransform.GetScale3D();
	
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (controlledPlatform == true)
	{		
		FVector NewLocation = GetActorLocation(); // Get Location of Actor
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime)); // Perform FMath function to move the object
		NewLocation.Y += DeltaHeight * RunningSpeed; //Scale our height by a factor of Running Speed (float)
		RunningTime += DeltaTime;
		SetActorLocation(NewLocation);

		UE_LOG(LogTemp, Warning, TEXT("Sin(RunningTime = %f"), DeltaHeight);
	}	

}

