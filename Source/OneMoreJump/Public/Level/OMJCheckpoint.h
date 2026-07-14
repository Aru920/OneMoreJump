#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJCheckpoint.generated.h"

class UPaperFlipbookComponent;
class USphereComponent;

UCLASS()
class ONEMOREJUMP_API AOMJCheckpoint : public AActor
{
	GENERATED_BODY()

public:
	AOMJCheckpoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperFlipbookComponent> CheckpointFlipbook;

private:
	UFUNCTION()
	void HandleCheckpointOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
