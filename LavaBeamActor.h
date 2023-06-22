
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LavaBeamActor.generated.h"

class UCapsuleComponent;
UCLASS()
class GP03T06_API ALavaBeamActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALavaBeamActor();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
