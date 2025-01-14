// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowlingBall.generated.h"

class UProjectileMovementComponent;

UCLASS(Abstract)
class MINERVA_API ABowlingBall : public AActor
{
	GENERATED_BODY()

public:
	ABowlingBall();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MovementComponent;
};
