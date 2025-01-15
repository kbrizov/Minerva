// Christian Rizov's Minerva

#include "BowlingPinFormation.h"
#include "BowlingPin.h"

ABowlingPinFormation::ABowlingPinFormation()
{
	PrimaryActorTick.bCanEverTick = false;
}

#if WITH_EDITOR
void ABowlingPinFormation::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SpawnBowlingPins();
}

void ABowlingPinFormation::Destroyed()
{
	DespawnBowlingPins();
	Super::Destroyed();
}
#endif

void ABowlingPinFormation::BeginPlay()
{
	Super::BeginPlay();
	SpawnBowlingPins();
}

void ABowlingPinFormation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DespawnBowlingPins();
	Super::EndPlay(EndPlayReason);
}

void ABowlingPinFormation::SpawnBowlingPins()
{
	if (!ensure(BowlingPinClass))
	{
		return;
	}

	if (!BowlingPins.IsEmpty())
	{
		DespawnBowlingPins();
	}

	UWorld* World = GetWorld();
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
			BowlingPin->SetFlags(RF_Transient);
			BowlingPins.Add(BowlingPin);
		}
	}
}

void ABowlingPinFormation::DespawnBowlingPins()
{
	for (ABowlingPin* BowlingPin : BowlingPins)
	{
		check(BowlingPin);
		BowlingPin->Destroy();
	}

	BowlingPins.Empty();
}
