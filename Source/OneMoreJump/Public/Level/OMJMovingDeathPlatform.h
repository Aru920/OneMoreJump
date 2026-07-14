#pragma once

#include "CoreMinimal.h"
#include "Level/OMJMovingPlatform.h"
#include "OMJMovingDeathPlatform.generated.h"

UCLASS()
class ONEMOREJUMP_API AOMJMovingDeathPlatform : public AOMJMovingPlatform
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandlePlatformOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
