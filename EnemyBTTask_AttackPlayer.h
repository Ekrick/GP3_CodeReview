
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyBTTask_AttackPlayer.generated.h"


UCLASS()
class GP03T06_API UEnemyBTTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UEnemyBTTask_AttackPlayer();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
