
#pragma once

#include "CoreMinimal.h"
#include "BossAbility.h"
#include "BA_LavaFloor.generated.h"


class ALavaPoolActor;
UCLASS()
class GP03T06_API UBA_LavaFloor : public UBossAbility
{
	GENERATED_BODY()
private:
	TArray<TObjectPtr<ALavaPoolActor>> InnerPoolArray;
	TArray<TObjectPtr<ALavaPoolActor>> OuterPoolArray;

	TObjectPtr<UChildActorComponent> SpawnCenter;

	FVector DormantPosition = FVector(0,0, -500);
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ActivateAbility() override;
	virtual void DeactivateAbility() override;

	void DormantPools(TArray<TObjectPtr<ALavaPoolActor>>& poolArray);
	void RingOfPools(TArray<TObjectPtr<ALavaPoolActor>>& poolArray, float radius);
	void SpawnPools(TArray<TObjectPtr<ALavaPoolActor>>& poolArray, int poolAmount);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InnerPoolAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int OuterPoolAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InnerRadius = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OuterRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lava Pool")
	TSubclassOf<ALavaPoolActor> LavaPoolActor;
	
	UFUNCTION(BlueprintCallable)
	virtual void UseAbility() override;
};
