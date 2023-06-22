
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemySpreadManager.generated.h"


UCLASS()
class GP03T06_API UEnemySpreadManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UEnemySpreadManager();

private:
	int NumberOfPositions = 20;
	TArray<float> PositionArray;
	TArray<bool> FreeSpots;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void GeneratePositions();

	bool CheckCloser(FVector currentPosition, FVector oldPosition, FVector newPosition);

public:
	int GetIndex(FVector pawnPosition, float range);

	float GetAngle(int index) { return PositionArray[index]; }

	void ResetPosition(int positionIndex);
};
