// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatforms.generated.h"


UCLASS()
class ADVENGAME_API AMovingPlatforms : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatforms();

	// declare Function to turn platform on
	UFUNCTION(BlueprintCallable, Category = "Light Switch")
		void TogglePlatform();


	UPROPERTY(EditAnywhere, Category = "Platform")
		float speedOfPlatform;
	UPROPERTY(EditAnywhere, Category = "Platform")
		float firstEnd;
	UPROPERTY(EditAnywhere, Category = "Platform")
		float secondEnd;
	UPROPERTY(EditAnywhere, Category = "Platform")
		bool isDiagonal;
	UPROPERTY(EditAnywhere, Category = "Platform")
		bool isActivatable;

	bool Activated;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	
};
