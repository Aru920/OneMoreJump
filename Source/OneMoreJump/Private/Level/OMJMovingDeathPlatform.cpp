#include "Level/OMJMovingDeathPlatform.h"

#include "PaperTileMapComponent.h"
#include "Player/OMJPlayerCharacter.h"

void AOMJMovingDeathPlatform::BeginPlay()
{
	Super::BeginPlay();

	PlatformTileMap->OnComponentBeginOverlap.AddDynamic(this, &AOMJMovingDeathPlatform::HandlePlatformOverlap);
	PlatformTileMap->OnComponentHit.AddDynamic(this, &AOMJMovingDeathPlatform::HandlePlatformHit);
}

void AOMJMovingDeathPlatform::HandlePlatformOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	KillPlayerIfNeeded(OtherActor);
}

void AOMJMovingDeathPlatform::HandlePlatformHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	KillPlayerIfNeeded(OtherActor);
}

void AOMJMovingDeathPlatform::KillPlayerIfNeeded(AActor* OtherActor)
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->Die();
	}
}
