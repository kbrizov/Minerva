// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowlingPinSpawner.generated.h"

class ABowlingPin;

UCLASS(Abstract)
class MINERVA_API ABowlingPinSpawner : public AActor
{
	GENERATED_BODY()

public:
	ABowlingPinSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TArray<TObjectPtr<ABowlingPin>> BowlingPins;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BowlingPinClass;

	void SpawnBowlingPins();
	void DespawnBowlingPins();
};
