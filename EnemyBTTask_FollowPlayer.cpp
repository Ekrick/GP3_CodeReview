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

//task that runs when player has been spotted
//chase the player but try to move to an assigned position around the player (so as to not clump up with other enemies)
EBTNodeResult::Type UEnemyBTTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	TObjectPtr<UEnemySpreadManager> PositionManager = GetWorld()->GetSubsystem<UEnemySpreadManager>(); 
	float AttackRange{};

	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();
	const TObjectPtr<AEnemyBase> AIPawn = Cast<AEnemyBase>(AIController->GetPawn());
	TObjectPtr<UBlackboardComponent> BlackboardComponent = AIController->GetBlackboardComponent();
	const TObjectPtr<APawn> Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	//null checks
	if (!IsValid(Player) || !IsValid(AIPawn) || !IsValid(BlackboardComponent) || !IsValid(PositionManager))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("Follow Player Failed"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	

	//checks if this unit is ranged or melee

	if (AIPawn->IsRanged)
	{
		AttackRange = BlackboardComponent->GetValueAsFloat("ProjectileRange");
	}
	else
	{
		AttackRange = BlackboardComponent->GetValueAsFloat("MeleeRange");
	}

	//if the unit hasn't been given a position, assign a position (with the position manager)
	if (!AIPawn->AssignedManagerPosition)
	{
		AIPawn->PositionIndex = PositionManager->GetIndex(AIPawn->GetActorLocation(), AttackRange);
		AIPawn->AssignedAngle = PositionManager->GetAngle(AIPawn->PositionIndex);
		AIPawn->AssignedManagerPosition = true;
	}

	// get the position you should move to
	FVector PlayerPos = Player->GetActorLocation();
	FVector TargetPos = FindPointOnCircle(PlayerPos, AIPawn->AssignedAngle, AttackRange*RangeBufferValue);
	
	const TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	//checking if in range to attack, if not move to the position you are assigned
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

	//if you are in range to attack set "in range" to true
	if (DistanceToPlayer.Size() <= AttackRange)
	{
		AIPawn->SetInRange(true);
		
		//if you haven't reached your position yet but are within an acceptable range of it, start attacking (flip bool in blackboard)
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

//get your position around the player from your assigned angle
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
