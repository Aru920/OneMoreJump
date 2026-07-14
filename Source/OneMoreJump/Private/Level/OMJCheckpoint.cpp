#include "Level/OMJCheckpoint.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PaperFlipbookComponent.h"
#include "Player/OMJPlayerCharacter.h"

AOMJCheckpoint::AOMJCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetSphereRadius(40.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CheckpointFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CheckpointFlipbook"));
	CheckpointFlipbook->SetupAttachment(Collision);
	CheckpointFlipbook->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AOMJCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AOMJCheckpoint::HandleCheckpointOverlap);
}

void AOMJCheckpoint::HandleCheckpointOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetCheckpointLocation(GetActorLocation());
		UKismetSystemLibrary::PrintString(this, TEXT("Checkpoint reached"), true, true, FLinearColor::Green, 1.5f);
	}
}
