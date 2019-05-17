// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NPC.generated.h"

UCLASS()
class ADVENGAME_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC(const class FObjectInitializer& PCIP);

	// The sphere collider that the player has to collide with to trigger the event (get
	// item, display messages etc.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		USphereComponent* ProxSphere;

	// This is the NPC's message that he will tell us
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		FString NpcMessage;

	// This is the NPC's name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString Name;

	// This adds the ability to add a textured background for the text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		UTexture2D* Face;

	// When you create a blueprint from this class, you want to be
	// able to edit that message in blueprints,
	// that's why we have the 'EditAnywhere' and 'BlueprintReadWrite' properties

	// The function Prox is to create the new collider Sphere
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void InProximity(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult & SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
