// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowlingPin.generated.h"

UCLASS(Abstract)
class MINERVA_API ABowlingPin : public AActor
{
	GENERATED_BODY()

public:
	ABowlingPin();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> Pivot;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
