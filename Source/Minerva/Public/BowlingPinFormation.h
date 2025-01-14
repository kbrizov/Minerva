// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowlingPinFormation.generated.h"

class ABowlingPin;

UCLASS(Abstract)
class MINERVA_API ABowlingPinFormation : public AActor
{
	GENERATED_BODY()

public:
	ABowlingPinFormation();

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
