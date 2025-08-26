// Christian Rizov's Minerva.

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
    
    bool IsStanding() const;

private:
    UPROPERTY(VisibleDefaultsOnly)
    TObjectPtr<USceneComponent> Pivot;

    UPROPERTY(VisibleDefaultsOnly)
    TObjectPtr<UStaticMeshComponent> Mesh;
};
