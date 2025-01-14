// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MinervaGameMode.generated.h"

UCLASS(Abstract)
class MINERVA_API AMinervaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SpawnBowlingPins() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BowlingPinClass;
};
