// Christian Rizov's Minerva

#include "BowlingPlayerController.h"
#include "BowlingBall.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void ABowlingPlayerController::BeginPlay()
{
	Super::BeginPlay();
	BowlingBallStartLocation = FindBowlingBallStartLocation();
	SpawnBowlingBall();
}

void ABowlingPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DespawnBowlingBall();
	BowlingBallStartLocation = nullptr;
	Super::EndPlay(EndPlayReason);
}

void ABowlingPlayerController::SpawnBowlingBall()
{
	if (!ensure(BowlingBallClass))
	{
		return;
	}

	if (!ensure(BowlingBallStartLocation))
	{
		return;
	}

	UWorld* World =  GetWorld();
	const FVector BowlingBallLocation = BowlingBallStartLocation->GetActorLocation();
	const FRotator BowlingBallRotation = BowlingBallStartLocation->GetActorRotation();
	BowlingBall = World->SpawnActor<ABowlingBall>(BowlingBallClass, BowlingBallLocation, BowlingBallRotation);
	check(BowlingBall);
	BowlingBall->SetFlags(RF_Transient);
}

void ABowlingPlayerController::DespawnBowlingBall()
{
	if (BowlingBall)
	{
		BowlingBall->Destroy();
		BowlingBall = nullptr;
	}
}

void ABowlingPlayerController::RestBowlingBallLocation()
{
	check(BowlingBall);
	check(BowlingBallStartLocation);
	BowlingBall->SetActorLocationAndRotation(BowlingBallStartLocation->GetActorLocation(), BowlingBallStartLocation->GetActorRotation());
}

TObjectPtr<ATargetPoint> ABowlingPlayerController::FindBowlingBallStartLocation() const
{
	TArray<AActor*> OutTargetPoints;
	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), OutTargetPoints);

	if (OutTargetPoints.IsEmpty())
	{
		return nullptr;
	}

	return StaticCast<ATargetPoint*>(OutTargetPoints[0]);
}
