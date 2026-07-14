#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJSlimeBlock.generated.h"

class AOMJPlayerCharacter;
class UPaperTileMapComponent;

UCLASS()
class ONEMOREJUMP_API AOMJSlimeBlock : public AActor
{
	GENERATED_BODY()

public:
	AOMJSlimeBlock();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperTileMapComponent> SlimeTileMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bounce")
	float BounceStrength = 900.f;

private:
	UFUNCTION()
	void HandleSlimeHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
};
