#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJCoin.generated.h"

class UPaperFlipbookComponent;
class USphereComponent;

UCLASS()
class ONEMOREJUMP_API AOMJCoin : public AActor
{
	GENERATED_BODY()

public:
	AOMJCoin();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Coin")
	void OnCoinCollected();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperFlipbookComponent> CoinFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin")
	float DestroyDelay = 0.35f;

private:
	UFUNCTION()
	void HandleCoinOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	bool bCollected = false;
};
