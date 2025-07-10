// Christian Rizov's Minerva.

#include "BowlingBall.h"

ABowlingBall::ABowlingBall()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    check(Mesh);
    Mesh->SetSimulatePhysics(true);
    Mesh->SetEnableGravity(true);
    RootComponent = Mesh;
}

void ABowlingBall::Launch(float Force)
{
    check(Mesh);
    Mesh->SetEnableGravity(true);
    const FVector Impulse = GetActorForwardVector() * Force;
    Mesh->AddImpulse(Impulse);
}

void ABowlingBall::SetEnableGravity(bool bEnableGravity)
{
    check(Mesh);
    Mesh->SetEnableGravity(bEnableGravity);
}

void ABowlingBall::ResetVelocity()
{
    check(Mesh);
    Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
    Mesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

bool ABowlingBall::IsIdle() const
{
    const bool bIsIdle = FMath::IsNearlyZero(GetVelocity().SquaredLength());
    return bIsIdle;
}
