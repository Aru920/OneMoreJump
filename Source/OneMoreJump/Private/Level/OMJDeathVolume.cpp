#include "Level/OMJDeathVolume.h"

#include "Kismet/KismetSystemLibrary.h"
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
}

void AOMJDeathVolume::HandleDeathTileMapOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && OtherActor->IsA<AOMJPlayerCharacter>())
	{
		UKismetSystemLibrary::PrintString(this, TEXT("Dead"), true, true, FLinearColor::Red, 2.f);
	}
}
