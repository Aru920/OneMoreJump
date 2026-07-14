#include "Level/OMJPropellerBelt.h"

#include "PaperTileMapComponent.h"
#include "Player/OMJPlayerCharacter.h"

AOMJPropellerBelt::AOMJPropellerBelt()
{
	PrimaryActorTick.bCanEverTick = false;

	BeltTileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("BeltTileMap"));
	SetRootComponent(BeltTileMap);
}

void AOMJPropellerBelt::BeginPlay()
{
	Super::BeginPlay();

	BeltTileMap->OnComponentBeginOverlap.AddDynamic(this, &AOMJPropellerBelt::HandleBeltOverlap);
	BeltTileMap->OnComponentHit.AddDynamic(this, &AOMJPropellerBelt::HandleBeltHit);
}

void AOMJPropellerBelt::HandleBeltOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	LaunchPlayerIfNeeded(OtherActor);
}

void AOMJPropellerBelt::HandleBeltHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	LaunchPlayerIfNeeded(OtherActor);
}

void AOMJPropellerBelt::LaunchPlayerIfNeeded(AActor* OtherActor)
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor))
	{
		const float Direction = bLaunchRight ? 1.f : -1.f;
		const FVector LaunchVelocity(ForwardLaunchStrength * Direction, 0.f, UpLaunchStrength);
		PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}
}
