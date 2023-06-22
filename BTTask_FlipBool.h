
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FlipBool.generated.h"


UCLASS()
class GP03T06_API UBTTask_FlipBool : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FlipBool();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
