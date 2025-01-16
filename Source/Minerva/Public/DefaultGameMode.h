// Christian Rizov's Minerva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultGameMode.generated.h"

UCLASS(Abstract)
class MINERVA_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	static constexpr int32 TotalFrames = 10;
	static constexpr int32 MaxRolls = 21; // Maximum rolls in a game, including bonus rolls
	static constexpr int32 MaxPins = 10;

	int32 CurrentFrame = 1;
	int32 CurrentRoll = 1;
	int32 PinsPerRoll[MaxRolls] = {0};
	int32 RollIndex = 0;

	template<typename T>
	T* GetPlayerController()
	{
		static_assert(TIsDerivedFrom<T, APlayerController>::IsDerived, "T must be derived from APlayerController.");
		return Cast<T>(UGameplayStatics::GetPlayerController(this, 0));
	}

	UFUNCTION()
	void OnRollCompleted(uint32 DownedPins);

	int32 CalculateScore() const;

	void HandleRegularFrame(int32 DownedPins);
	void HandleTenthFrame(int32 PinsKnockedDown);
	void AdvanceFrame();

	bool IsRollValid(int32 DownedPins) const { return 0 <= DownedPins && DownedPins <= MaxPins; }
	bool IsTenthFrame() const { return CurrentFrame == TotalFrames; }

	bool IsStrike(int32 InRollIndex) const { return PinsPerRoll[InRollIndex] == MaxPins; }
	bool IsSpare(int32 InRollIndex) const { return PinsPerRoll[InRollIndex] + PinsPerRoll[InRollIndex + 1] == MaxPins; }
};
