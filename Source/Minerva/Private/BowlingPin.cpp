// Christian Rizov's Minerva

#include "BowlingPin.h"

ABowlingPin::ABowlingPin()
{
	PrimaryActorTick.bCanEverTick = false;

	Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
	check(Pivot);
	RootComponent = Pivot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);
	Mesh->SetupAttachment(Pivot);
}

