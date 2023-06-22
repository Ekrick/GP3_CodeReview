

#include "LavaPoolActor.h"

ALavaPoolActor::ALavaPoolActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ALavaPoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALavaPoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

