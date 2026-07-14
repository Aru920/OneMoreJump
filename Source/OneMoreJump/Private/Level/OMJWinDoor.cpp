#include "Level/OMJWinDoor.h"

#include "PaperTileMapComponent.h"
#include "Player/OMJPlayerCharacter.h"

AOMJWinDoor::AOMJWinDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorTileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("DoorTileMap"));
	SetRootComponent(DoorTileMap);
}

void AOMJWinDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorTileMap->OnComponentBeginOverlap.AddDynamic(this, &AOMJWinDoor::HandleDoorOverlap);
	DoorTileMap->OnComponentHit.AddDynamic(this, &AOMJWinDoor::HandleDoorHit);
}

void AOMJWinDoor::HandleDoorOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	WinPlayerIfNeeded(OtherActor);
}

void AOMJWinDoor::HandleDoorHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	WinPlayerIfNeeded(OtherActor);
}

void AOMJWinDoor::WinPlayerIfNeeded(AActor* OtherActor)
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->Win();
	}
}
