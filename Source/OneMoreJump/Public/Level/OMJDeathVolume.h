#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJDeathVolume.generated.h"

class UPaperTileMapComponent;

UCLASS()
class ONEMOREJUMP_API AOMJDeathVolume : public AActor
{
	GENERATED_BODY()

public:
	AOMJDeathVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperTileMapComponent> DeathTileMap;

private:
	UFUNCTION()
	void HandleDeathTileMapOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleDeathTileMapHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

	void KillPlayerIfNeeded(AActor* OtherActor);
};
