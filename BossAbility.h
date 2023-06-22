
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossAbility.generated.h"

class ABoss;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP03T06_API UBossAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBossAbility();

private:
	bool isUsable = true;

protected:
	const float TAU = 6.28;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Settings")
	float Duration = 5.f;
	float counter = 0.f;
	bool AbilityActive = false;
	TObjectPtr<ABoss> Owner;
	
	virtual void BeginPlay() override;
	virtual void ActivateAbility() { AbilityActive = true; }
	virtual void DurationTimer(float DeltaTime);

public:	
	virtual void UseAbility() {}
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void DeactivateAbility() { AbilityActive = false; } 

	UFUNCTION(BlueprintCallable)
	bool CheckActive() { return AbilityActive; }
	
	UFUNCTION(BlueprintCallable)
	bool CheckUsable() { return isUsable; }

	UFUNCTION(BlueprintCallable)
	void MakeUsable() { isUsable = true; }
};
