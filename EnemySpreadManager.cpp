

#include "EnemySpreadManager.h"

#include "EnemyAIControllerBase.h"

UEnemySpreadManager::UEnemySpreadManager()
{
	
}

void UEnemySpreadManager::OnWorldBeginPlay(UWorld& InWorld)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Got Manager"));

	GeneratePositions();

}

int UEnemySpreadManager::GetIndex(FVector pawnPosition, float range)
{
	int PositionIndex {};
	
	FVector PlayerPosition;
	
	TObjectPtr<APawn> Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!IsValid(Player))
	{
		return NULL;
	}
	PlayerPosition = Player->GetActorLocation();

	FVector CurrentPosition ;
	
	for (int i = 0; i < NumberOfPositions; i++)
	{
		FVector AngleVector = FVector::Zero();
		AngleVector.X = FMath::Cos(PositionArray[i]);
		AngleVector.Y = FMath::Sin(PositionArray[i]);
		AngleVector *= range;

		FVector TempPosition = PlayerPosition + AngleVector;
		
		if (FreeSpots[i])
		{
			if (i == 0 || CheckCloser(pawnPosition, CurrentPosition, TempPosition) )
			{
				CurrentPosition = TempPosition;
				PositionIndex = i;
			}
		}
	}
	FreeSpots[PositionIndex] = false;
	return PositionIndex;
}

void UEnemySpreadManager::GeneratePositions()
{
	float TAU = 6.28f;
	
	for (int i = 0; i < NumberOfPositions; i++)
	{
		float angle = TAU/NumberOfPositions * i;
		PositionArray.Add(angle);
		FreeSpots.Add(true);
	}
}

bool UEnemySpreadManager::CheckCloser(FVector currentPosition, FVector oldPosition, FVector newPosition)
{
	float oldRange = (oldPosition - currentPosition).Length();

	float newRange = (newPosition - currentPosition).Length();

	if (newRange < oldRange)
		return true;
	return false;
}

void UEnemySpreadManager::ResetPosition(int positionIndex)
{
	FreeSpots[positionIndex] = true;
}

