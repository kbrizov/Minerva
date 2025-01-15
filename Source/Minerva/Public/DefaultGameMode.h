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
	template<typename T>
	T* GetPlayerController()
	{
		static_assert(TIsDerivedFrom<T, APlayerController>::IsDerived, "T must be derived from APlayerController.");
		return Cast<T>(UGameplayStatics::GetPlayerController(this, 0));
	}

	UFUNCTION()
	void OnRollCompleted(uint32 DownedPins);
};
