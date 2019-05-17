// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItem.h"
#include "PlayerActor.h"
#include "MyHUD.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"


// Sets default values
APickupItem::APickupItem(const class FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = "UKNOWN ITEM";
	Quantity = 0;
	Score = 0; // Score to be added

	PrimaryActorTick.bCanEverTick = true;
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	RootComponent = Mesh;
	//Mesh->SetSimulatePhysics(true);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
	ProxSphere->SetupAttachment(Mesh);
}

void APickupItem::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<APlayerActor>(OtherActor) == nullptr)
	{
		return;
	}
	// Retrieve the Avatar Class in this case 'APlayerActor' 
	// Then access the 'Pickup' method of this class in the 'PickupItem' class
	APlayerActor* avatar = Cast<APlayerActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); 

	// Retrieve the player Controller as it is a global method
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	// Attach the HUD to the player controller so it follows if the object moves
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	
	// The pickup Message here is reused the same way it was used in the NPC class
	hud->addMessage(Message(Icon, FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, 5.f, FColor::White));
	hud->addScore(Score);

	if (Name == "KEY")
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Orange, "Key");
		// Set key to true
		avatar->keyCaptured();
	}

	avatar->Pickup(this);



	Destroy();
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

