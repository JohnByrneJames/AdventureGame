

#include "DoorAccessable.h"
#include "Engine.h"


// Sets default values
ADoorAccessable::ADoorAccessable(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("HOLD"));

	Door = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Door"));
	Door->SetupAttachment(RootComponent);
	doorFrame = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DoorFrame"));
	doorFrame->SetupAttachment(Door);

}

// Called when the game starts or when spawned
void ADoorAccessable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorAccessable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorAccessable::ToggleOpen()
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Emerald, "Door Destroyed");
	Destroy(this);
}

