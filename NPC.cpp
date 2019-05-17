// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "MyHUD.h"
#include "PlayerActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"



// Sets default values
ANPC::ANPC(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this character to call Tick() every frame.  
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));

	// You must attach the ProxSphere to the root component, otherwise,
	// the ProxSphere will NOT be with the NPC!
	ProxSphere->SetupAttachment(RootComponent);
	ProxSphere->SetSphereRadius(32.f);

	// Code to make ANPC::InProximity() run when this proximity sphere
	// overlaps another actor.
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::InProximity);
	NpcMessage = "Nice to meet you Traveler, I am Albert."; // Default message, can be edited in blueprints
}

void ANPC::InProximity_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{
	// this is where the code on "what to do when a collision is detected" goes.
	// if the overlapped actor is the player, display the message
	// Begin by casting 'OtherActor' so even only takes whilst they are in proximity of the NPC
	AActor *player = Cast<APlayerActor>(OtherActor); 

	// If no 'OtherActor' is detected during cast, the cast will return 'nullptr'
	if (player == nullptr)
	{
		// The interesected actor wasn't the player, so ignore this overlap
		return;
	}

	// The player object has multiple components. So we don't want an overlap event
	// for EACH component, so just check for intersection with the player's root component.
	if (OtherComp != player->GetRootComponent())
	{
		return;
	}

	// HUD object that is attached to the player controller to allow passing of the message
	APlayerController * PController = GetWorld()->GetFirstPlayerController();
	AMyHUD * hud = Cast<AMyHUD>(PController->GetHUD());

	// Pass a message from the NPC to the HUD | The message is displayed whenever the player is within
	// the collision sphere.
	//hud->addMessage(Message(NpcMessage, 5.f, FColor::White));

	// Displays the name of the NPC aswell
	//hud->addMessage(Message(Name + FString(": ") + NpcMessage, 5.f, FColor::White));

	//Displats the texture in this case a face
	hud->addMessage(Message(Face, NpcMessage, 5.f, FColor::White));
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

