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

bool ABowlingPin::IsStanding() const
{
	const bool bIsIdle = FMath::IsNearlyZero(GetVelocity().SquaredLength());

	const FVector ActorUpVector = Mesh->GetUpVector();
	const FVector WorldUpVector = FVector::UpVector;
	const float DotProduct = FVector::DotProduct(WorldUpVector, ActorUpVector);
	const bool bSameDirection = FMath::IsNearlyEqual(DotProduct, 1.f);

	const bool bIsStanding = bIsIdle && bSameDirection;

	return bIsStanding;
}
