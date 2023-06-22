
#include "EnemyBTTask_RandomRoaming.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemyBTTask_RandomRoaming::UEnemyBTTask_RandomRoaming()
{
	NodeName = TEXT("Random Roaming");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UEnemyBTTask_RandomRoaming, BlackboardKey));
}


EBTNodeResult::Type UEnemyBTTask_RandomRoaming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	FNavLocation Location{};

	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	const TObjectPtr<APawn> AIPawn = AIController->GetPawn();

	const FVector Origin = AIPawn->GetActorLocation();

	const TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, RoamRange, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
}

FString UEnemyBTTask_RandomRoaming::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}