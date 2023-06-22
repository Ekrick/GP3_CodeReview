

#include "BA_LavaBeam.h"
#include "LavaBeamActor.h"
#include "Boss.h"


void UBA_LavaBeam::BeginPlay()
{
	Super::BeginPlay();

	Spawn_1 = Owner->GetLavaPoint1();
	Spawn_2 = Owner->GetLavaPoint2();

	
	LavaBeam_1 = GetWorld()->SpawnActor<ALavaBeamActor>(LavaBeamActor, Owner->GetActorLocation(), Owner->GetActorRotation());
	LavaBeam_2 = GetWorld()->SpawnActor<ALavaBeamActor>(LavaBeamActor, Owner->GetActorLocation(), Owner->GetActorRotation());

	DeactivateAbility();
	// ActivateAbility();
}

void UBA_LavaBeam::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	if (AbilityActive)
	{
		AlignBeams();
		TurnClockwise(DeltaTime);
	}
}

void UBA_LavaBeam::UseAbility()
{
	ActivateAbility();
}


void UBA_LavaBeam::TurnClockwise(float DeltaTime)
{
	const float FrameSpeed = RotationSpeed * DeltaTime;

	FQuat QuatRotation = FQuat(FRotator(0.f,FrameSpeed, 0.f));
	Owner->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void UBA_LavaBeam::AlignBeams()
{
	if (LavaBeam_1 == nullptr || LavaBeam_2 == nullptr)
		return;

	FVector Position_1 = Spawn_1->GetComponentLocation();
	FVector Position_2 = Spawn_2->GetComponentLocation();

	
	LavaBeam_1->SetActorRotation(SetRotation(LavaBeam_1, Position_1));
	LavaBeam_1->SetActorLocation(Position_1);

	LavaBeam_2->SetActorRotation(SetRotation(LavaBeam_2, Position_2));
	LavaBeam_2->SetActorLocation(Position_2);
}

FRotator UBA_LavaBeam::SetRotation(TObjectPtr<ALavaBeamActor> Beam, FVector SpawnPoint)
{
	FVector BeamVector = SpawnPoint - Owner->GetActorLocation();
	FRotator BeamRotator = BeamVector.Rotation();

	BeamRotator.Pitch = 0;
	BeamRotator.Roll = 0;

	return BeamRotator;

}



void UBA_LavaBeam::ActivateAbility()
{
	Super::ActivateAbility();
	
	if (LavaBeam_1 == nullptr || LavaBeam_2 == nullptr)
		return;

	AlignBeams();
}

void UBA_LavaBeam::DeactivateAbility()
{
	Super::DeactivateAbility();
	
	if (LavaBeam_1 == nullptr || LavaBeam_2 == nullptr)
		return;

	const FVector  DormantPosition = FVector(0, 0, -1000);

	LavaBeam_1->SetActorLocation(DormantPosition);
	LavaBeam_2->SetActorLocation(DormantPosition);

}
