#include "EnemyAttack_Projectile.h"
#include "Components/BoxComponent.h"

AEnemyAttack_Projectile::AEnemyAttack_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionArea"));
	SetRootComponent(BoxComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	static FName MeshCollisionProfileName(TEXT("Projectile Mesh"));
	StaticMesh->SetCollisionProfileName(MeshCollisionProfileName);

}

void AEnemyAttack_Projectile::BeginPlay()
{
	Super::BeginPlay();

	Reset();
}

void AEnemyAttack_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProjectileMovement(DeltaTime);
	LifetimeTimer(DeltaTime);
}

void AEnemyAttack_Projectile::Reset()
{
	MoveSpeed = ProjectileSpeed;
	IsActive = true;
	LifeTimer = 0.f;
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);
}

void AEnemyAttack_Projectile::Disappear()
{
	this->AddActorWorldOffset(FVector(0, 0, -1000.f));
	IsActive = false;
	LifeTimer = 0.f;
	MoveSpeed = 0.f;
	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
}

void AEnemyAttack_Projectile::ProjectileMovement(float DeltaTime)
{
	FVector ActorPosition = this->GetActorLocation();
	FVector MoveDirection = this->GetActorForwardVector();
	ActorPosition += MoveDirection * MoveSpeed * DeltaTime;

	SetActorLocation(ActorPosition);
}

void AEnemyAttack_Projectile::LifetimeTimer(float DeltaTime)
{
	if (!IsActive)
		return;
	
	if (LifeTimer >= ProjectileLifetime)
	{
		Disappear();
		return;
	}
	LifeTimer += DeltaTime;
}


