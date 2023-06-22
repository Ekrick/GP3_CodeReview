
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyBTTask_RandomRoaming.generated.h"


UCLASS()
class GP03T06_API UEnemyBTTask_RandomRoaming : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UEnemyBTTask_RandomRoaming();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roaming Range", meta = (AllowPrivateAccess = true))
	float RoamRange {100.f};
};
