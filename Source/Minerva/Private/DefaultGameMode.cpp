// Christian Rizov's Minerva

#include "DefaultGameMode.h"
#include "BowlingPlayerController.h"

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ABowlingPlayerController* PlayerController = GetPlayerController<ABowlingPlayerController>())
	{
		PlayerController->OnRollCompletedDelegate.AddDynamic(this, &ADefaultGameMode::OnRollCompleted);
	}
}

void ADefaultGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ABowlingPlayerController* PlayerController = GetPlayerController<ABowlingPlayerController>())
	{
	    PlayerController->OnRollCompletedDelegate.RemoveDynamic(this, &ADefaultGameMode::OnRollCompleted);
	}

	Super::EndPlay(EndPlayReason);
}

void ADefaultGameMode::OnRollCompleted(uint32 DownedPins)
{
	UKismetSystemLibrary::PrintString(
	   this,
	   FString::Printf(TEXT("Roll completed with %d pins downed!"), DownedPins),
	   true,  // bPrintToScreen
	   false, // bPrintToLog
	   FLinearColor::Yellow, // Text color
	   5.0f  // Duration
   );
}
