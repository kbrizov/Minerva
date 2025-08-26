// Christian Rizov's Minerva.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "BowlingPlayerController.generated.h"

class ABowlingBall;
class ABowlingPinFormation;
class ATargetPoint;
class UEnhancedInputLocalPlayerSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRollCompletedDelegate, uint32, DownedPins);

UCLASS(Abstract)
class MINERVA_API ABowlingPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    FRollCompletedDelegate OnRollCompletedDelegate;

    UFUNCTION(BlueprintCallable, Category = "Input", meta = (AutoCreateRefTerm = "Options"))
    virtual void AddInputMappingContext(const UInputMappingContext* MappingContext, int32 Priority, const FModifyContextOptions& Options = FModifyContextOptions());

    UFUNCTION(BlueprintCallable, Category = "Input", meta = (AutoCreateRefTerm = "Options"))
    virtual void RemoveInputMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options = FModifyContextOptions());

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void ClearAllInputMappingContexts();

    ABowlingBall* GetBowlingBall() const { return BowlingBall; }
    ABowlingPinFormation* GetBowlingPinFormation() const { return BowlingPinFormation; }

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintCallable)
    void OnMoveBowlingBall(FVector MovementInput);

    UFUNCTION(BlueprintCallable)
    void OnThrowBowlingBall(bool bValue);

    UFUNCTION(BlueprintCallable)
    void OnResetBowlingBall(bool bValue);

private:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ABowlingBall> BowlingBallClass;

    UPROPERTY(Transient)
    TObjectPtr<ABowlingBall> BowlingBall;

    UPROPERTY(Transient)
    TObjectPtr<ATargetPoint> BowlingBallStartLocation;

    UPROPERTY(Transient)
    TObjectPtr<ABowlingPinFormation> BowlingPinFormation;

    void SpawnBowlingBall();
    void DespawnBowlingBall();

    ATargetPoint* FindBowlingBallStartLocation() const;
    ABowlingPinFormation* FindBowlingPinFormation() const;

    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
};
