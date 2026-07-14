#include "Level/OMJDeathVolume.h"

#include "PaperTileMapComponent.h"
#include "Player/OMJPlayerCharacter.h"

AOMJDeathVolume::AOMJDeathVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	DeathTileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("DeathTileMap"));
	SetRootComponent(DeathTileMap);
}

void AOMJDeathVolume::BeginPlay()
{
	Super::BeginPlay();

	DeathTileMap->OnComponentBeginOverlap.AddDynamic(this, &AOMJDeathVolume::HandleDeathTileMapOverlap);
	DeathTileMap->OnComponentHit.AddDynamic(this, &AOMJDeathVolume::HandleDeathTileMapHit);
}

void AOMJDeathVolume::HandleDeathTileMapOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	KillPlayerIfNeeded(OtherActor);
}

void AOMJDeathVolume::HandleDeathTileMapHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	KillPlayerIfNeeded(OtherActor);
}

void AOMJDeathVolume::KillPlayerIfNeeded(AActor* OtherActor)
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->Die();
	}
}
