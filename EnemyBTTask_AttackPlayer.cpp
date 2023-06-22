#include "EnemyBTTask_AttackPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyBase.h"
#include "EnemySpreadManager.h"


UEnemyBTTask_AttackPlayer::UEnemyBTTask_AttackPlayer()
{
	NodeName = TEXT("Check Attack Range");

	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UEnemyBTTask_AttackPlayer, BlackboardKey));
}

EBTNodeResult::Type UEnemyBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float AttackRange{};

	TObjectPtr<UEnemySpreadManager> PositionManager = GetWorld()->GetSubsystem<UEnemySpreadManager>(); 
	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	TObjectPtr<UBlackboardComponent> BlackboardComponent = AIController->GetBlackboardComponent();
	const TObjectPtr<AEnemyBase> AIPawn = Cast<AEnemyBase>(AIController->GetPawn());
	const TObjectPtr<APawn> Player = GetWorld()->GetFirstPlayerController()->GetPawn();

		
	if (!IsValid(Player) || !IsValid(AIPawn) || !IsValid(BlackboardComponent) || !IsValid(PositionManager))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}


	bool Ranged = AIPawn->IsRanged;
	
	if (Ranged)
	{
		AttackRange = BlackboardComponent->GetValueAsFloat("ProjectileRange");
	}
	else
	{
		AttackRange = BlackboardComponent->GetValueAsFloat("MeleeRange");
	}

	FVector DistanceToPlayer = Player->GetActorLocation() - AIPawn->GetActorLocation();
	if (DistanceToPlayer.Size() > AttackRange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("NOT IN RANGE"));

		AIPawn->SetInRange(false);
		AIPawn->ResetPosition();
		
		BlackboardComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, false);
	}

	AIPawn->LookAtTarget();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

FString UEnemyBTTask_AttackPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Bool: %s"), *BlackboardKey.SelectedKeyName.ToString());
}