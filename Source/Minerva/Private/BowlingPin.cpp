// Christian Rizov's Minerva

#include "BowlingPin.h"

ABowlingPin::ABowlingPin()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

