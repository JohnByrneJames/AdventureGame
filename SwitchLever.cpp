// Fill out your copyright notice in the Description page of Project Settings.

#include "SwitchLever.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "MovingPlatforms.h"


// Sets default values
ASwitchLever::ASwitchLever()
{
	PrimaryActorTick.bCanEverTick = true;

	LightIntensity = 3000.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = LightIntensity;
	PointLight->bVisible = true;
	RootComponent = PointLight;

	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	LightSphere->InitSphereRadius(300.0f);
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	LightSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	LightSphere->SetupAttachment(RootComponent);
}

void ASwitchLever::ToggleLight()
{
	PointLight->ToggleVisibility();
}
