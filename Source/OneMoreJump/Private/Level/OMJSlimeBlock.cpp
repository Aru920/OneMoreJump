#include "Level/OMJSlimeBlock.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PaperTileMapComponent.h"
#include "Player/OMJPlayerCharacter.h"

AOMJSlimeBlock::AOMJSlimeBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	SlimeTileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("SlimeTileMap"));
	SetRootComponent(SlimeTileMap);
	SlimeTileMap->SetNotifyRigidBodyCollision(true);
}

void AOMJSlimeBlock::BeginPlay()
{
	Super::BeginPlay();

	SlimeTileMap->OnComponentHit.AddDynamic(this, &AOMJSlimeBlock::HandleSlimeHit);
}

void AOMJSlimeBlock::HandleSlimeHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter) || PlayerCharacter->GetVelocity().Z > 0.f)
	{
		return;
	}

	PlayerCharacter->LaunchCharacter(FVector(0.f, 0.f, BounceStrength), false, true);
}
