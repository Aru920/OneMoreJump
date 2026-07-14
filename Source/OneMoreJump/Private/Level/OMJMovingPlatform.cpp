#include "Level/OMJMovingPlatform.h"

#include "PaperTileMapComponent.h"

AOMJMovingPlatform::AOMJMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformTileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("PlatformTileMap"));
	SetRootComponent(PlatformTileMap);
}

void AOMJMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	MoveSign = StartDirection == EOMJPlatformStartDirection::Positive ? 1.f : -1.f;
}

void AOMJMovingPlatform::SetMoveSpeed(float NewMoveSpeed)
{
	MoveSpeed = FMath::Max(0.f, NewMoveSpeed);
}

void AOMJMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MoveDistance <= 0.f || MoveSpeed <= 0.f)
	{
		return;
	}

	MoveOffset += MoveSpeed * MoveSign * DeltaSeconds;

	const float MinOffset = StartDirection == EOMJPlatformStartDirection::Negative ? -MoveDistance : 0.f;
	const float MaxOffset = StartDirection == EOMJPlatformStartDirection::Negative ? 0.f : MoveDistance;

	if (MoveOffset >= MaxOffset)
	{
		MoveOffset = MaxOffset;
		MoveSign = -1.f;
	}
	else if (MoveOffset <= MinOffset)
	{
		MoveOffset = MinOffset;
		MoveSign = 1.f;
	}

	const FVector MoveAxis = MoveDirection == EOMJPlatformMoveDirection::LeftRight
		? FVector::XAxisVector
		: FVector::ZAxisVector;

	SetActorLocation(StartLocation + MoveAxis * MoveOffset, true);
}
