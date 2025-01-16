// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowlingPinFormation.generated.h"

class ABowlingPin;

/**
 * Represents a typical ten-pin triangle bowling formation.
 */
UCLASS(Abstract)
class MINERVA_API ABowlingPinFormation : public AActor
{
	GENERATED_BODY()

public:
	ABowlingPinFormation();

	uint8 GetDownedPinsCount() const;
	uint8 GetStandingPinsCount() const;

	void ResetPins();

#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;
#endif

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TArray<TObjectPtr<ABowlingPin>> BowlingPins;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BowlingPinClass;

	UPROPERTY(EditDefaultsOnly)
	float SpaceBetweenPins = 30.48; // The standard space between pins in cm.

	void SpawnBowlingPins();
	void DespawnBowlingPins();
};
