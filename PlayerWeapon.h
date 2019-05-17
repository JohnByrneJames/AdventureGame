// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class ADVENGAME_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon(const class FObjectInitializer& PCIP);

	// Weapon Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float Damage;

	AActor * User;

	// the sphere you collide with to do impact damage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		UCapsuleComponent* ProxCapsule;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
