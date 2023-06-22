
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

class UNavArea_Obstacle;
class UEnemyProjectile_Pooling;
class AEnemyAttack_Projectile;
class UStaticMeshComponent;
class UEnemySpreadManager;

UCLASS()
class GP03T06_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()
	
public:	
	AEnemyBase();
	
private:
	float PositionTimerFloat = 0.f;
	bool IsInRange = false;

	void AttackCooldown(float DeltaTime);

	void PositionTimer(float DeltaTime);

	TObjectPtr<UEnemySpreadManager> PositionManager;
	TObjectPtr<UEnemyProjectile_Pooling> Pooler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RangedAttack", meta = (AllowPrivateAccess = true))
	TObjectPtr<UChildActorComponent> ChildActor;


protected:
	virtual void BeginPlay() override;

public:
	float AssignedAngle = 0.f;
	
	bool AssignedManagerPosition = false;
	int PositionIndex;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Attack")
	TObjectPtr<AActor> SpawnPointActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Attack")
	bool IsRanged = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Attack")
	TSubclassOf<AEnemyAttack_Projectile> SpawnedProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ranged Attack")
	bool CanShoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged Attack")
	float RangeAttackInterval = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	float TimeUntilReset = 2.f;
	
	
	UFUNCTION(BlueprintCallable)
	void LookAtTarget();
	
	UFUNCTION(BlueprintCallable)
	void RangedAttack();

	UFUNCTION(BlueprintCallable)
	void ResetPosition();

	UFUNCTION(BlueprintCallable)
	bool GetInRange() { return IsInRange; }

	UFUNCTION(BlueprintCallable)
	void SetInRange(bool inValue) { IsInRange = inValue; }
};
