// Christian Rizov's Minerva.

#include "DefaultGameMode.h"

#include "BowlingPinFormation.h"
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
    check(IsRollValid(DownedPins));

    PinsPerRoll[RollIndex] = DownedPins;
    RollIndex++;

    if (!IsTenthFrame())
    {
        HandleRegularFrame(DownedPins);
    }
    else
    {
        HandleTenthFrame(DownedPins);
    }

    const bool bShouldEndGame = CurrentFrame > TotalFrames;
    if (bShouldEndGame)
    {
        int32 PlayerScore = CalculateScore();
        UKismetSystemLibrary::PrintString(
            this,
            FString::Printf(TEXT("FINAL SCORE: %d !!!"), PlayerScore),
            true,
            false,
            FLinearColor::Yellow,
            5.0f);
    }
}

int32 ADefaultGameMode::CalculateScore() const
{
    int32 Score = 0;
    int32 Roll = 0;

    for (int32 Frame = 0; Frame < TotalFrames; ++Frame)
    {
        if (IsStrike(Roll))
        {
            constexpr int32 StrikePoints = MaxPins;
            const int32 StrikeBonusPoints = PinsPerRoll[Roll + 1] + PinsPerRoll[Roll + 2];

            Score += (StrikePoints + StrikeBonusPoints);
            Roll++;
        }
        else if (IsSpare(Roll))
        {
            constexpr int32 SparePoints = MaxPins;
            const int32 SpareBonusPoints = PinsPerRoll[Roll + 2];

            Score += (SparePoints + SpareBonusPoints);
            Roll += 2;
        }
        else
        {
            Score += (PinsPerRoll[Roll] + PinsPerRoll[Roll + 1]);
            Roll += 2;
        }
    }

    return Score;
}

void ADefaultGameMode::HandleRegularFrame(int32 DownedPins)
{
    if (CurrentRoll == 1 && DownedPins == MaxPins) // Strike!
    {
        AdvanceFrame();
    }
    else if (CurrentRoll == 2) // End the frame.
    {
        AdvanceFrame();
    }
    else
    {
        CurrentRoll++;
    }
}

void ADefaultGameMode::HandleTenthFrame(int32 DownedPins)
{
    if (CurrentRoll == 3) // Third roll ends the frame.
    {
        AdvanceFrame();
    }
    else if (CurrentRoll == 2) // Check if a third roll is needed.
    {
        if (IsStrike(RollIndex - 2) || IsSpare(RollIndex - 2))
        {
            CurrentRoll++; // Allow the third roll.
        }
        else
        {
            AdvanceFrame(); // No third roll for an open frame.
        }
    }
    else
    {
        CurrentRoll++; // Move to the second roll
    }
}

void ADefaultGameMode::AdvanceFrame()
{
    CurrentFrame++;
    CurrentRoll = 1;

    // TODO: Find a more suitable place to reset the bowling pins.
    const ABowlingPlayerController* PlayerController = GetPlayerController<ABowlingPlayerController>();
    check(PlayerController);

    ABowlingPinFormation* BowlingPinFormation = PlayerController->GetBowlingPinFormation();
    check(BowlingPinFormation);
    BowlingPinFormation->ResetPins();
}
