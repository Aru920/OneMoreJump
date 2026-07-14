#include "Level/OMJCoin.h"

#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "PaperFlipbookComponent.h"
#include "Player/OMJPlayerCharacter.h"

AOMJCoin::AOMJCoin()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetSphereRadius(24.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CoinFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CoinFlipbook"));
	CoinFlipbook->SetupAttachment(Collision);
	CoinFlipbook->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AOMJCoin::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AOMJCoin::HandleCoinOverlap);
}

void AOMJCoin::HandleCoinOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bCollected)
	{
		return;
	}

	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor))
	{
		bCollected = true;
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayerCharacter->CollectCoin();
		OnCoinCollected();
		SetLifeSpan(DestroyDelay);
	}
}
