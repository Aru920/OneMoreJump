#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMJMovingPlatform.generated.h"

class UPaperTileMapComponent;

UENUM(BlueprintType)
enum class EOMJPlatformMoveDirection : uint8
{
	LeftRight,
	TopBottom
};

UCLASS()
class ONEMOREJUMP_API AOMJMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AOMJMovingPlatform();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperTileMapComponent> PlatformTileMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	EOMJPlatformMoveDirection MoveDirection = EOMJPlatformMoveDirection::LeftRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = "0.0"))
	float MoveDistance = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = "0.0"))
	float MoveSpeed = 120.f;

private:
	FVector StartLocation = FVector::ZeroVector;
	float MoveOffset = 0.f;
	float MoveSign = 1.f;
};
