// Christian Rizov's Minerva

#include "BowlingPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "BowlingBall.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void ABowlingPlayerController::AddInputMappingContext(const UInputMappingContext* MappingContext, int32 Priority, const FModifyContextOptions& Options)
{
	if (IEnhancedInputSubsystemInterface* Subsystem = GetEnhancedInputSubsystem())
	{
		Subsystem->AddMappingContext(MappingContext, Priority, Options);
	}
}

void ABowlingPlayerController::RemoveInputMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options)
{
	if (IEnhancedInputSubsystemInterface* Subsystem = GetEnhancedInputSubsystem())
	{
		Subsystem->RemoveMappingContext(MappingContext, Options);
	}
}

void ABowlingPlayerController::ClearAllInputMappingContexts()
{
	if (IEnhancedInputSubsystemInterface* Subsystem = GetEnhancedInputSubsystem())
	{
		Subsystem->ClearAllMappings();
	}
}

void ABowlingPlayerController::BeginPlay()
{
	Super::BeginPlay();
	BowlingBallStartLocation = FindBowlingBallStartLocation();
	SpawnBowlingBall();
}

void ABowlingPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DespawnBowlingBall();
	BowlingBallStartLocation = nullptr;
	Super::EndPlay(EndPlayReason);
}

void ABowlingPlayerController::OnMoveBowlingBall(FVector MovementInput)
{
	if(!ensure(BowlingBall))
	{
		return;
	}

	const FVector CurrentLocation = BowlingBall->GetActorLocation();
	const FVector NewLocation = CurrentLocation + MovementInput;
	BowlingBall->SetActorLocation(NewLocation);
}

void ABowlingPlayerController::OnThrowBowlingBall(bool bValue)
{
	if(!ensure(BowlingBall))
	{
		return;
	}

	BowlingBall->Launch(5000);
}


void ABowlingPlayerController::SpawnBowlingBall()
{
	if (!ensure(BowlingBallClass))
	{
		return;
	}

	if (!ensure(BowlingBallStartLocation))
	{
		return;
	}

	UWorld* World =  GetWorld();
	const FVector BowlingBallLocation = BowlingBallStartLocation->GetActorLocation();
	const FRotator BowlingBallRotation = BowlingBallStartLocation->GetActorRotation();
	BowlingBall = World->SpawnActor<ABowlingBall>(BowlingBallClass, BowlingBallLocation, BowlingBallRotation);
	check(BowlingBall);
	BowlingBall->SetFlags(RF_Transient);
	BowlingBall->SetEnableGravity(false);
}

void ABowlingPlayerController::DespawnBowlingBall()
{
	if (BowlingBall)
	{
		BowlingBall->Destroy();
		BowlingBall = nullptr;
	}
}

void ABowlingPlayerController::RestBowlingBallLocation()
{
	check(BowlingBall);
	check(BowlingBallStartLocation);
	BowlingBall->SetActorLocationAndRotation(BowlingBallStartLocation->GetActorLocation(), BowlingBallStartLocation->GetActorRotation());
}

TObjectPtr<ATargetPoint> ABowlingPlayerController::FindBowlingBallStartLocation() const
{
	TArray<AActor*> OutTargetPoints;
	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), OutTargetPoints);

	if (OutTargetPoints.IsEmpty())
	{
		return nullptr;
	}

	return StaticCast<ATargetPoint*>(OutTargetPoints[0]);
}

UEnhancedInputLocalPlayerSubsystem* ABowlingPlayerController::GetEnhancedInputSubsystem() const
{
	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	}

	return nullptr;
}
