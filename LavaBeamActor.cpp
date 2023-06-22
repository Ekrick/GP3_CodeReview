

#include "LavaBeamActor.h"

#include "Components/CapsuleComponent.h"

ALavaBeamActor::ALavaBeamActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ALavaBeamActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALavaBeamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

