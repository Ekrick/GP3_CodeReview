
#include "BTTask_FlipBool.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FlipBool::UBTTask_FlipBool()
{
	NodeName = TEXT("Flip Bool");

	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FlipBool, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FlipBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	TObjectPtr<UBlackboardComponent> BlackboardComponent = AIController->GetBlackboardComponent();


	if (BlackboardComponent->GetValueAsBool(BlackboardKey.SelectedKeyName))
	{
		BlackboardComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, false);
	}
	else
	{
		BlackboardComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, true);
	}
	
	
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_FlipBool::GetStaticDescription() const
{
	return FString::Printf(TEXT("Bool: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
