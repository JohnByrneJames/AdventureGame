// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorAccessable.generated.h"

UCLASS()
class ADVENGAME_API ADoorAccessable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorAccessable(const class FObjectInitializer& PCIP);

	// delcare toggle to destroy door when key is collected
	UFUNCTION(BlueprintCallable, Category = "Light Switch")
		void ToggleOpen();

	// declare sphere comp
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class UStaticMeshComponent* Door;

	// declare sphere comp
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class UStaticMeshComponent* doorFrame;


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	
	
};
