// Christian Rizov's Minerva.

#include "BowlingBall.h"

ABowlingBall::ABowlingBall()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetSimulatePhysics(true);
    Mesh->SetEnableGravity(true);
    
    RootComponent = Mesh;
}

void ABowlingBall::Launch(float Force)
{
    Mesh->SetEnableGravity(true);
    const FVector Impulse = GetActorForwardVector() * Force;
    Mesh->AddImpulse(Impulse);
}

void ABowlingBall::SetEnableGravity(bool bEnableGravity)
{
    Mesh->SetEnableGravity(bEnableGravity);
}

void ABowlingBall::ResetVelocity()
{
    Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
    Mesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

bool ABowlingBall::IsIdle() const
{
    const bool bIsIdle = FMath::IsNearlyZero(GetVelocity().SquaredLength());
    return bIsIdle;
}
