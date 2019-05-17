// Fill out your copyright notice in the Description page of Project Settings.

#include "BobbingCube.h"
#include "Components/TimelineComponent.h"


// Sets default values
ABobbingCube::ABobbingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotatableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RotatableMesh"));

	AnimTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("AnimationTrigger"));
	AnimTrigger->SetGenerateOverlapEvents(true);
	AnimTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABobbingCube::OnAnimTriggered);
	AnimTrigger->SetupAttachment(RotatableMesh); //FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

// Called when the game starts or when spawned
void ABobbingCube::BeginPlay()
{
	Super::BeginPlay();
	/*
	if (AnimCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleProgress"));
		MyTimeline.AddInterpFloat(AnimCurve, ProgressFunction);
		MyTimeline.SetLooping(false);
		InitialRotation = TargetRotation = GetActorRotation();
		if (RotationAxis == "Yaw")
		{
			TargetRotation.Yaw += MaxRotation;
		}
		else if (RotationAxis == "Pitch")
		{
			TargetRotation.Pitch += MaxRotation;
		}
		else if (RotationAxis == "Roll")
		{
			TargetRotation.Roll += MaxRotation;
		}
	}
	*/

	if (AnimCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleProgress"));
		MyTimeline.AddInterpFloat(AnimCurve, ProgressFunction);
		MyTimeline.SetLooping(false);
		InitialPosition = TargetPosition = GetActorLocation();
		if (TransformationAxis == "Z")
		{
			TargetPosition.Z += MaxSpeed;
		}
		if (TransformationAxis == "X")
		{
			TargetPosition.X += MaxSpeed;
		}
		if (TransformationAxis == "Y")
		{
			TargetPosition.Y += MaxSpeed;
		}

	}
	
}

// Called every frame
void ABobbingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MyTimeline.TickTimeline(DeltaTime);

}

void ABobbingCube::HandleProgress(float Value)
{
	FVector NewPosition = FMath::Lerp(InitialPosition, TargetPosition, Value);
	SetActorLocation(NewPosition);
}

void ABobbingCube::OnAnimTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (!MyTimeline.IsPlaying())
	{
		MyTimeline.PlayFromStart();
	}
}



