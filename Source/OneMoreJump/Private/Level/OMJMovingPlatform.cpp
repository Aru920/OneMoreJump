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
}

void AOMJMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MoveDistance <= 0.f || MoveSpeed <= 0.f)
	{
		return;
	}

	MoveOffset += MoveSpeed * MoveSign * DeltaSeconds;

	if (MoveOffset >= MoveDistance)
	{
		MoveOffset = MoveDistance;
		MoveSign = -1.f;
	}
	else if (MoveOffset <= 0.f)
	{
		MoveOffset = 0.f;
		MoveSign = 1.f;
	}

	const FVector MoveAxis = MoveDirection == EOMJPlatformMoveDirection::LeftRight
		? FVector::XAxisVector
		: FVector::ZAxisVector;

	SetActorLocation(StartLocation + MoveAxis * MoveOffset, true);
}
