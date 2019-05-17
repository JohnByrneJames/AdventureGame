// Fill out your copyright notice in the Description page of Project Settings.

#include "DualActivation.h"
#include "Components/TimelineComponent.h"
#include "Engine.h"


// Sets default values
ADualActivation::ADualActivation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADualActivation::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADualActivation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




