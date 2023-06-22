

#include "EnemyProjectile_Pooling.h"
#include "EnemyAttack_Projectile.h"

void UEnemyProjectile_Pooling::OnWorldBeginPlay(UWorld& InWorld)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Got Pooler"));
	
}


void UEnemyProjectile_Pooling::ProjectilePooler(FVector spawnPoint, FRotator direction, TSubclassOf<AEnemyAttack_Projectile> spawnedProjectile)
{
	TObjectPtr<AEnemyAttack_Projectile> pooledprojectile = ProjectileArray[0];
	if (!pooledprojectile->GetActive())
	{
		pooledprojectile->Reset();
		pooledprojectile->SetActorLocation(spawnPoint);
		pooledprojectile->SetActorRotation(direction);
		ProjectileArray.RemoveSingle(pooledprojectile);
		ProjectileArray.Add(pooledprojectile);
	}
}

void UEnemyProjectile_Pooling::FillPool(TSubclassOf<AEnemyAttack_Projectile> spawnedProjectile)
{
	if (ProjectileArray.IsEmpty())
	{
		TObjectPtr<AEnemyAttack_Projectile> newprojectile = SpawnObject(FVector::Zero(), FRotator::ZeroRotator, spawnedProjectile);
		ProjectileArray.Add(newprojectile);
		newprojectile->Reset();
		newprojectile->Disappear();
	}
	else if (ProjectileArray.Num() < ProjectileCount)
	{
		TObjectPtr<AEnemyAttack_Projectile> newprojectile = SpawnObject(FVector::Zero(), FRotator::ZeroRotator, spawnedProjectile);
		ProjectileArray.Add(newprojectile);
		newprojectile->Reset();
		newprojectile->Disappear();
	}
}


TObjectPtr<AEnemyAttack_Projectile> UEnemyProjectile_Pooling::SpawnObject(FVector spawnPoint, FRotator direction, TSubclassOf<AEnemyAttack_Projectile> spawnedProjectile)
{

	TObjectPtr<AEnemyAttack_Projectile> spawnobject = GetWorld()->SpawnActor<AEnemyAttack_Projectile>(spawnedProjectile, spawnPoint, direction);
	if (IsValid(spawnobject))
	{
		return spawnobject;
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString("Failed Spawn"));
	return NULL;
}
