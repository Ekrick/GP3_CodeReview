
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyBTTask_CheckLineOfSight.generated.h"

class UAIPerceptionComponent;

UCLASS()
class GP03T06_API UEnemyBTTask_CheckLineOfSight : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UEnemyBTTask_CheckLineOfSight();
	
private:
	bool CheckPerceived(TObjectPtr<UAIPerceptionComponent> PerceptionComponent);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual FString GetStaticDescription() const override;
};
