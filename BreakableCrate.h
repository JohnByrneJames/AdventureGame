// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "BreakableCrate.generated.h"

UCLASS()
class ADVENGAME_API ABreakableCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableCrate(const class FObjectInitializer& PCIP);

	// How much damage the bullet does.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float HitPoints;

	// Crate drops
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		UClass *BPLoot;

	// Collision Sphere around the box
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		UBoxComponent* ProxBox;

	// Mesh for Crate
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		UStaticMeshComponent* Mesh;

	// Explosion to play on box break
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		UParticleSystemComponent *Explosion;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	//Spawn the Loot at the location the box was destroyed
	void lootDrop();


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
	
};
