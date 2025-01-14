// Christian Rizov's Minerva

#include "MinervaGameMode.h"

void AMinervaGameMode::SpawnBowlingPins() const
{
	UWorld* World = GetWorld();
	constexpr float SpaceBetweenPins = 100.0f;
	constexpr int Rows = 4;

	for (int32 Row = 0; Row < Rows; ++Row)
	{
		const int32 PinsInRow = Row + 1;
		const float X = Row * SpaceBetweenPins;

		for (int32 Pin = 0; Pin < PinsInRow; ++Pin)
		{
			const float Y = (Pin - ((PinsInRow - 1) / 2.0f)) * SpaceBetweenPins;
			const FVector PinPosition = FVector(X, Y, 0.0f);

			World->SpawnActor<AActor>(BowlingPinClass, PinPosition, FRotator::ZeroRotator);
		}
	}
}

void AMinervaGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnBowlingPins();
}
