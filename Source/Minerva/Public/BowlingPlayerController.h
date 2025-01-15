// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "BowlingPlayerController.generated.h"

class ABowlingBall;
class ATargetPoint;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(Abstract)
class MINERVA_API ABowlingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (AutoCreateRefTerm = "Options"))
	virtual void AddInputMappingContext(const UInputMappingContext* MappingContext, int32 Priority, const FModifyContextOptions& Options = FModifyContextOptions());

	UFUNCTION(BlueprintCallable, Category = "Input", meta = (AutoCreateRefTerm = "Options"))
	virtual void RemoveInputMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options = FModifyContextOptions());

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void ClearAllInputMappingContexts();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void OnMoveBowlingBall(FVector MovementInput);

	UFUNCTION(BlueprintCallable)
	void OnThrowBowlingBall(bool bValue);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABowlingBall> BowlingBallClass;

	UPROPERTY()
	TObjectPtr<ABowlingBall> BowlingBall;

	UPROPERTY()
	TObjectPtr<ATargetPoint> BowlingBallStartLocation;

	void SpawnBowlingBall();
	void DespawnBowlingBall();
	void RestBowlingBallLocation();
	TObjectPtr<ATargetPoint> FindBowlingBallStartLocation() const;

	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
};
