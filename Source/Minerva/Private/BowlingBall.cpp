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
	MovementComponent->SetAutoActivate(false);
	MovementComponent->UpdatedComponent = RootComponent;

	EnableMovement(false);
}

void ABowlingBall::Launch()
{
	EnableMovement(true);
}

void ABowlingBall::EnableMovement(bool bValue)
{
	check(MovementComponent);
	MovementComponent->SetActive(bValue);

	check(Mesh);
	Mesh->SetSimulatePhysics(bValue);
	Mesh->SetEnableGravity(bValue);
}

