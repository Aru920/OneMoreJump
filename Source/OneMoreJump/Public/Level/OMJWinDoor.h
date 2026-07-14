#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJWinDoor.generated.h"

class UPaperTileMapComponent;

UCLASS()
class ONEMOREJUMP_API AOMJWinDoor : public AActor
{
	GENERATED_BODY()

public:
	AOMJWinDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperTileMapComponent> DoorTileMap;

private:
	UFUNCTION()
	void HandleDoorOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleDoorHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

	void WinPlayerIfNeeded(AActor* OtherActor);
};
