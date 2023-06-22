
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemyProjectile_Pooling.generated.h"

class AEnemyAttack_Projectile;

UCLASS()
class GP03T06_API UEnemyProjectile_Pooling : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	float SpawnOffsetValue = 100.f;
	
	int ProjectileCount = 20;


public:
	TArray<TObjectPtr<AEnemyAttack_Projectile>> ProjectileArray;

	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	void ProjectilePooler(FVector spawnPoint, FRotator direction, TSubclassOf<AEnemyAttack_Projectile> spawnedProjectile);

	void FillPool(TSubclassOf<AEnemyAttack_Projectile> spawnedProjectile);

	TObjectPtr<AEnemyAttack_Projectile> SpawnObject(FVector spawnPoint, FRotator direction, TSubclassOf<AEnemyAttack_Projectile> spawnedProjectile);
};
