// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveFloat.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "BobbingCube.generated.h"

UCLASS()
class ADVENGAME_API ABobbingCube : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	ABobbingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Axis to rotate on
	UPROPERTY(EditAnywhere)
		FString TransformationAxis = "Z";

	// Static mesh for rotatable object
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* RotatableMesh;

	// Box trigger to start the animation
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* AnimTrigger;

	// Maximum spin that the object will reach
	UPROPERTY(EditAnywhere, Category = "Animation")
		float MaxSpeed;

	// Pointer to CurveFloat instance
	UPROPERTY(EditAnywhere, Category = "Animation")
		UCurveFloat* AnimCurve;
	
private:

	// Initial rotation
	FVector InitialPosition;

	// Target rotation
	FVector TargetPosition;

	// Timeline to spin
	FTimeline MyTimeline;

	UFUNCTION()
		void HandleProgress(float Value);

	UFUNCTION()
		void OnAnimTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	
};
