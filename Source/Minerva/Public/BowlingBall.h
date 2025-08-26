// Christian Rizov's Minerva.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BowlingBall.generated.h"

UCLASS(Abstract)
class MINERVA_API ABowlingBall : public AActor
{
    GENERATED_BODY()

public:
    ABowlingBall();
    
    void Launch(float Force);
    
    void SetEnableGravity(bool bEnableGravity);
    
    void ResetVelocity();
    
    bool IsIdle() const;
    
    bool IsMoving() const { return !IsIdle(); }

private:
    UPROPERTY(VisibleDefaultsOnly)
    TObjectPtr<UStaticMeshComponent> Mesh;
};
