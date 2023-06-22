#include "EnemyBTTask_FollowPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyBase.h"
#include "EnemySpreadManager.h"

UEnemyBTTask_FollowPlayer::UEnemyBTTask_FollowPlayer()
{
	NodeName = TEXT("Follow Player");

	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UEnemyBTTask_FollowPlayer, BlackboardKey));

}

EBTNodeResult::Type UEnemyBTTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	TObjectPtr<UEnemySpreadManager> PositionManager = GetWorld()->GetSubsystem<UEnemySpreadManager>(); 
	float AttackRange{};

	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	const TObjectPtr<AEnemyBase> AIPawn = Cast<AEnemyBase>(AIController->GetPawn());
	TObjectPtr<UBlackboardComponent> BlackboardComponent = AIController->GetBlackboardComponent();
	const TObjectPtr<APawn> Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!IsValid(Player) || !IsValid(AIPawn) || !IsValid(BlackboardComponent) || !IsValid(PositionManager))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("Follow Player Failed"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	



	if (AIPawn->IsRanged)
	{
		AttackRange = BlackboardComponent->GetValueAsFloat("ProjectileRange");
	}
	else
	{
		AttackRange = BlackboardComponent->GetValueAsFloat("MeleeRange");
	}
	
	if (!AIPawn->AssignedManagerPosition)
	{
		AIPawn->PositionIndex = PositionManager->GetIndex(AIPawn->GetActorLocation(), AttackRange);
		AIPawn->AssignedAngle = PositionManager->GetAngle(AIPawn->PositionIndex);
		AIPawn->AssignedManagerPosition = true;
	}

	
	FVector PlayerPos = Player->GetActorLocation();
	FVector TargetPos = FindPointOnCircle(PlayerPos, AIPawn->AssignedAngle, AttackRange*RangeBufferValue);
	
	const TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	bool IsInRange = AIPawn->GetInRange();
	if (!IsInRange)
	{
		if (IsValid(NavSystem) && NavSystem->ProjectPointToNavigation(TargetPos, Location))
		{
			AIController->MoveToLocation(Location.Location, AcceptableRadius);
			AIPawn->LookAtTarget();
		}
	}

	FVector DistanceToPlayer = PlayerPos - AIPawn->GetActorLocation();
	FVector DistanceToPosition = TargetPos - AIPawn->GetActorLocation();

	if (DistanceToPlayer.Size() <= AttackRange)
	{
		AIPawn->SetInRange(true);
		if (DistanceToPosition.Size() <= AcceptableRadius * 5)
		{
			BlackboardComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, true);
		}
	}
	else
	{
		AIPawn->SetInRange(false);

	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FVector UEnemyBTTask_FollowPlayer::FindPointOnCircle(FVector center, float angle, float radius)
{
	FVector AngleVector = FVector::Zero();
	
	AngleVector.X = FMath::Cos(angle);
	AngleVector.Y = FMath::Sin(angle);
	

	FVector OutVector = center + AngleVector * radius;
	
	return OutVector;
}


FString UEnemyBTTask_FollowPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Bool: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
