#include "Level/OMJMovingDeathPlatform.h"

#include "Kismet/KismetSystemLibrary.h"
#include "PaperTileMapComponent.h"
#include "Player/OMJPlayerCharacter.h"

void AOMJMovingDeathPlatform::BeginPlay()
{
	Super::BeginPlay();

	PlatformTileMap->OnComponentBeginOverlap.AddDynamic(this, &AOMJMovingDeathPlatform::HandlePlatformOverlap);
}

void AOMJMovingDeathPlatform::HandlePlatformOverlap(
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
