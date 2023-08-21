

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

//method to get a position around the player
int UEnemySpreadManager::GetIndex(FVector pawnPosition, float range)
{
	int PositionIndex {};
	
	FVector PlayerPosition;
	//get location of the player
	TObjectPtr<APawn> Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!IsValid(Player))
	{
		return NULL;
	}
	PlayerPosition = Player->GetActorLocation();

	FVector CurrentPosition ;

	//search through the list of angles to find the one closest to you
	for (int i = 0; i < NumberOfPositions; i++)
	{
		FVector AngleVector = FVector::Zero();
		AngleVector.X = FMath::Cos(PositionArray[i]);
		AngleVector.Y = FMath::Sin(PositionArray[i]);
		AngleVector *= range;

		FVector TempPosition = PlayerPosition + AngleVector;

		//find the angle position that is closest to you current position
		if (FreeSpots[i])
		{
			if (i == 0 || CheckCloser(pawnPosition, CurrentPosition, TempPosition) )
			{
				CurrentPosition = TempPosition;
				PositionIndex = i;
			}
		}
	}

	//reserve the angle position for this unit
	FreeSpots[PositionIndex] = false;
	return PositionIndex;
}

//create a list of angles around the player
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

// return the closest of two positions
bool UEnemySpreadManager::CheckCloser(FVector currentPosition, FVector oldPosition, FVector newPosition)
{
	float oldRange = (oldPosition - currentPosition).Length();

	float newRange = (newPosition - currentPosition).Length();

	if (newRange < oldRange)
		return true;
	return false;
}

//free up the position to be usable again
void UEnemySpreadManager::ResetPosition(int positionIndex)
{
	FreeSpots[positionIndex] = true;
}

