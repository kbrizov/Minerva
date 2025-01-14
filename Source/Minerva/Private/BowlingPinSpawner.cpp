// Christian Rizov's Minerva

#include "BowlingPinSpawner.h"
#include "BowlingPin.h"

ABowlingPinSpawner::ABowlingPinSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABowlingPinSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnBowlingPins();
}

void ABowlingPinSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DespawnBowlingPins();
	Super::EndPlay(EndPlayReason);
}

void ABowlingPinSpawner::SpawnBowlingPins()
{
	if (!ensure(BowlingPinClass))
	{
		return;
	}

	UWorld* World = GetWorld();
	constexpr float SpaceBetweenPins = 30.48; // The standard space between pins in cm.
	constexpr int Rows = 4;

	for (int32 Row = 0; Row < Rows; ++Row)
	{
		const int32 PinsInRow = Row + 1;
		const float X = Row * SpaceBetweenPins;

		for (int32 Pin = 0; Pin < PinsInRow; ++Pin)
		{
			const float Y = (Pin - ((PinsInRow - 1) / 2.0f)) * SpaceBetweenPins;
			const FVector PinPosition = GetActorLocation() + FVector(X, Y, 0.0f);

			ABowlingPin* BowlingPin = Cast<ABowlingPin>(World->SpawnActor<AActor>(BowlingPinClass, PinPosition, FRotator::ZeroRotator));
			check(BowlingPin);
			BowlingPins.Add(BowlingPin);
		}
	}
}

void ABowlingPinSpawner::DespawnBowlingPins()
{
	for (ABowlingPin* BowlingPin : BowlingPins)
	{
		check(BowlingPin);
		BowlingPin->Destroy();
	}
}
