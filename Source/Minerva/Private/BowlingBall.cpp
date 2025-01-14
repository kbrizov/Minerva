// Christian Rizov's Minerva

#include "BowlingBall.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABowlingBall::ABowlingBall()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);
	RootComponent = Mesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	check(MovementComponent);
	MovementComponent->UpdatedComponent = RootComponent;
}

