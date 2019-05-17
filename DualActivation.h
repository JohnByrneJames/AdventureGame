// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"
#include "DualActivation.generated.h"

UCLASS()
class ADVENGAME_API ADualActivation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADualActivation();

	// declare sphere comp
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class USphereComponent* LightSphere;


	   
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



};
