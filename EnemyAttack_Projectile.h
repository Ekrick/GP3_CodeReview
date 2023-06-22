// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAttack_Projectile.generated.h"

class UBoxComponent;

UCLASS()
class GP03T06_API AEnemyAttack_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyAttack_Projectile();

private:
	bool IsActive = true;
	float MoveSpeed = 0.f;
	float LifeTimer = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box Collision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	void LifetimeTimer(float DeltaTime);
	void ProjectileMovement(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	
	void SetLocation(FVector position);
	bool GetActive() { return IsActive; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings", meta = (AllowPrivateAccess = "true"))
	float ProjectileLifetime;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Reset();
	
	UFUNCTION(BlueprintCallable)
		void Disappear();
};
