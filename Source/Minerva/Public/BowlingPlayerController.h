// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BowlingPlayerController.generated.h"

class ABowlingBall;
class ATargetPoint;

UCLASS(Abstract)
class MINERVA_API ABowlingPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABowlingBall> BowlingBallClass;

	UPROPERTY()
	TObjectPtr<ABowlingBall> BowlingBall;

	UPROPERTY()
	TObjectPtr<ATargetPoint> BowlingBallStartLocation;

	void SpawnBowlingBall();
	void DespawnBowlingBall();
	void RestBowlingBallLocation();
	TObjectPtr<ATargetPoint> FindBowlingBallStartLocation() const;
};
