// Christian Rizov's Minerva.

#include "BowlingPin.h"

ABowlingPin::ABowlingPin()
{
    PrimaryActorTick.bCanEverTick = false;

    Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
    RootComponent = Pivot;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Pivot);
}

bool ABowlingPin::IsStanding() const
{
    const FVector ActorUpVector = Mesh->GetUpVector();
    const FVector WorldUpVector = FVector::UpVector;
    const float DotProduct = FVector::DotProduct(WorldUpVector, ActorUpVector);
    const bool bIsStanding = FMath::IsNearlyEqual(DotProduct, 1.f, 0.2f);

    return bIsStanding;
}
