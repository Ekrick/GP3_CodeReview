

#include "BossAbility.h"
#include "Boss.h"

UBossAbility::UBossAbility()
{
	PrimaryComponentTick.bCanEverTick = true;

	Owner = Cast<ABoss>(GetOwner());
}


void UBossAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBossAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DurationTimer(DeltaTime);

}

void UBossAbility::DurationTimer(float DeltaTime)
{
	if (AbilityActive)
	{
		counter += DeltaTime;
		if (counter >= Duration)
		{
			DeactivateAbility();
			counter = 0;
		}
	}
}
