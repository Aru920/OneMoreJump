#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJPropellerBelt.generated.h"

class UPaperTileMapComponent;

UCLASS()
class ONEMOREJUMP_API AOMJPropellerBelt : public AActor
{
	GENERATED_BODY()

public:
	AOMJPropellerBelt();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperTileMapComponent> BeltTileMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Launch")
	float ForwardLaunchStrength = 900.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Launch")
	float UpLaunchStrength = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Launch")
	bool bLaunchRight = true;

private:
	UFUNCTION()
	void HandleBeltOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleBeltHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

	void LaunchPlayerIfNeeded(AActor* OtherActor);
};
