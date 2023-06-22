

#include "BA_LavaFloor.h"
#include "LavaPoolActor.h"
#include "Boss.h"

void UBA_LavaFloor::BeginPlay()
{
	Super::BeginPlay();

	SpawnCenter = Owner->GetPoolPoint();
	SpawnPools(InnerPoolArray, InnerPoolAmount);
	SpawnPools(OuterPoolArray, OuterPoolAmount);
}

void UBA_LavaFloor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBA_LavaFloor::UseAbility()
{
	ActivateAbility();
}

void UBA_LavaFloor::RingOfPools(TArray<TObjectPtr<ALavaPoolActor>>& poolArray, float radius)
{
	FVector CenterPosition = SpawnCenter->GetComponentLocation();

	if (poolArray.IsEmpty())
		return;
	
	for (int i = 0; i < poolArray.Num(); i++)
	{

		float angle = TAU/poolArray.Num() * i;
		TObjectPtr<ALavaPoolActor> Pool = poolArray[i];

		FVector AngleVector = FVector::Zero();

		AngleVector.X = FMath::Cos(angle);
		AngleVector.Y = FMath::Sin(angle);
		AngleVector *= radius;

		FVector OutVector = CenterPosition + AngleVector;
		Pool->SetActorLocation(OutVector);
	}
}

void UBA_LavaFloor::SpawnPools(TArray<TObjectPtr<ALavaPoolActor>>& poolArray, int poolAmount)
{
	if (poolArray.IsEmpty() || poolArray.Num() < poolAmount)
	{
		for (int i = 0; i < poolAmount; i++)
		{
			TObjectPtr<ALavaPoolActor> pool =  GetWorld()->SpawnActor<ALavaPoolActor>(LavaPoolActor, DormantPosition, FRotator::ZeroRotator);
			if (IsValid(pool))
			{
				poolArray.Add(pool);
			}
		}
	}
}

void UBA_LavaFloor::DormantPools(TArray<TObjectPtr<ALavaPoolActor>>& poolArray)
{
	for (int i = 0; i < poolArray.Num(); i++)
	{
		TObjectPtr<AActor> Pool = poolArray[i];

		Pool->SetActorLocation(DormantPosition);
	}
}



void UBA_LavaFloor::ActivateAbility()
{
	Super::ActivateAbility();

	if (InnerPoolArray.IsEmpty())
		SpawnPools(InnerPoolArray, InnerPoolAmount);
	
	RingOfPools(InnerPoolArray, InnerRadius);

	if (OuterPoolArray.IsEmpty())
		SpawnPools(OuterPoolArray, OuterPoolAmount);
	
	RingOfPools(OuterPoolArray, OuterRadius);
}

void UBA_LavaFloor::DeactivateAbility()
{
	Super::DeactivateAbility();

	DormantPools(InnerPoolArray);
	DormantPools(OuterPoolArray);
}