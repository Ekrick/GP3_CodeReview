
#include "EnemyBTTask_CheckLineOfSight.h"
#include "AIController.h"
#include "EnemyAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyBase.h"
#include "Perception/AIPerceptionComponent.h"


UEnemyBTTask_CheckLineOfSight::UEnemyBTTask_CheckLineOfSight()
{
	NodeName = TEXT("Check LoS");

	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UEnemyBTTask_CheckLineOfSight, BlackboardKey));
}

EBTNodeResult::Type UEnemyBTTask_CheckLineOfSight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	TObjectPtr<AEnemyAIControllerBase> AIController = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	TObjectPtr<UBlackboardComponent> BlackboardComponent = AIController->GetBlackboardComponent();
	const TObjectPtr<AEnemyBase> AIPawn = Cast<AEnemyBase>(AIController->GetPawn());
	const TObjectPtr<APawn> Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!IsValid(Player) || !IsValid(AIPawn) || !IsValid(BlackboardComponent))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	TObjectPtr<UAIPerceptionComponent> PerceptionComponent =  AIController->PerceptionComponent;
	if (IsValid(PerceptionComponent))
	{
		AIPawn->LookAtTarget();
		bool PlayerSpotted = CheckPerceived(PerceptionComponent);
		BlackboardComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, PlayerSpotted);
	}
	

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

FString UEnemyBTTask_CheckLineOfSight::GetStaticDescription() const
{
	return FString::Printf(TEXT("Bool: %s"), *BlackboardKey.SelectedKeyName.ToString());
}


bool UEnemyBTTask_CheckLineOfSight::CheckPerceived(TObjectPtr<UAIPerceptionComponent> PerceptionComponent)
{
	TArray<AActor*> ViewedActors {};
	PerceptionComponent->GetCurrentlyPerceivedActors(PerceptionComponent->GetDominantSense(), ViewedActors);

	if (ViewedActors.Num() > 0)
	{
		for (AActor* Actor : ViewedActors)
		{
			TObjectPtr<APawn> player = Cast<APawn>(Actor);
			if (IsValid(player) && player == GetWorld()->GetFirstPlayerController()->GetPawn())
			{
				return true;
			}
		}
	}
	return false;
}
