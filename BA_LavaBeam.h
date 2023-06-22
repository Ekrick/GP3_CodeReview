
#pragma once

#include "CoreMinimal.h"
#include "BossAbility.h"
#include "BA_LavaBeam.generated.h"


class ALavaBeamActor;
UCLASS()
class GP03T06_API UBA_LavaBeam : public UBossAbility
{
	GENERATED_BODY()
	
private:
	TObjectPtr<ALavaBeamActor> LavaBeam_1;
	TObjectPtr<ALavaBeamActor> LavaBeam_2;

	TObjectPtr<UChildActorComponent> Spawn_1;
	TObjectPtr<UChildActorComponent> Spawn_2;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ActivateAbility() override;
	virtual void DeactivateAbility() override;
	
	void TurnClockwise(float DeltaTime);
	void AlignBeams();
	FRotator SetRotation(TObjectPtr<ALavaBeamActor> Beam, FVector SpawnPoint);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lava Beam")
	TSubclassOf<ALavaBeamActor> LavaBeamActor;
	
	UFUNCTION(BlueprintCallable)
	virtual void UseAbility() override;



};
