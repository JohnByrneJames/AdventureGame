// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class ADVENGAME_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Time travelling in a certain direction
	UPROPERTY(EditAnywhere, Category = "Transformation Settings")
	float RunningTime;

	// Speed at which the object moves
	UPROPERTY(EditAnywhere, Category = "Transformation Settings")
	float RunningSpeed;

	// Platform moving or not
	UPROPERTY(EditAnywhere, Category = "Platform Type")
	bool controlledPlatform;
	
	
};
