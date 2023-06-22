
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyBTTask_FollowPlayer.generated.h"


UCLASS()
class GP03T06_API UEnemyBTTask_FollowPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UEnemyBTTask_FollowPlayer();

private:
	// float AttackRangeBuffer = 50.f;
	float RangeBufferValue = 0.7f;
	int AcceptableRadius = 20;
	
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	float GetRandomAngle() { return FMath::RandRange(0, 628) / 100; }
	
	FVector FindPointOnCircle(FVector center, float angle, float radius);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Mode", meta = (AllowPrivateAccess = true))
	bool IsRanged;
};

