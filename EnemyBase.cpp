
#include "EnemyBase.h"
#include "EnemyProjectile_Pooling.h"
#include "Components/StaticMeshComponent.h"
#include "EnemySpreadManager.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	
	ChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Ranged Attack Spawn-Point"));
	ChildActor->SetupAttachment(GetRootComponent());
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	Pooler = GetWorld()->GetSubsystem<UEnemyProjectile_Pooling>();
	PositionManager = GetWorld()->GetSubsystem<UEnemySpreadManager>();
}


void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PositionTimer(DeltaTime);
	
	Pooler->FillPool(SpawnedProjectile);
}

//shoot at the player
void AEnemyBase::RangedAttack()
{
	if (!IsValid(GetWorld()->GetFirstPlayerController()->GetPawn()))
		return;
	LookAtTarget();
	Pooler->ProjectilePooler(ChildActor->GetComponentLocation(), this->GetActorRotation(), SpawnedProjectile);
}

//turn to look at the player
void AEnemyBase::LookAtTarget()
{
	TObjectPtr<APawn> Target = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (IsValid(Target))
	{
		FVector TargetLocation = Target->GetActorLocation();	
		FVector MyLocation = this->GetActorLocation();
		TargetLocation.Z = MyLocation.Z;
		FVector LookVector = TargetLocation - MyLocation;

		FRotator LookDirection = LookVector.Rotation();

		this->SetActorRotation(LookDirection);
	}
}

//reset your given position around the player
void AEnemyBase::ResetPosition()
{
	AssignedManagerPosition = false;
	PositionManager->ResetPosition(PositionIndex);
	PositionTimerFloat = 0;
}

//if you've been out of range of the player for a given time you lose your spot
void AEnemyBase::PositionTimer(float DeltaTime)
{
	if(!AssignedManagerPosition || IsInRange)
	{
		PositionTimerFloat = 0;
		return;
	}
	
	PositionTimerFloat += DeltaTime;
	if (PositionTimerFloat >= TimeUntilReset)
	{
		ResetPosition();
	}
}






