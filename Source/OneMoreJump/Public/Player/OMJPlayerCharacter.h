#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "OMJPlayerCharacter.generated.h"

class UCameraComponent;
class UPaperFlipbook;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOMJCoinsChangedSignature, int32, CoinsCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOMJRunFinishedSignature, float, TimeTaken, int32, CoinsCollected);

UCLASS(Blueprintable)
class ONEMOREJUMP_API AOMJPlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AOMJPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Death")
	void Die();

	UFUNCTION(BlueprintCallable, Category = "Win")
	void Win();

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpointLocation(FVector NewCheckpointLocation);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Coins")
	void CollectCoin();

	UFUNCTION(BlueprintPure, Category = "Coins")
	int32 GetCoinsCollected() const;

	UFUNCTION(BlueprintPure, Category = "Time")
	float GetElapsedTime() const;

	UPROPERTY(BlueprintAssignable, Category = "Coins")
	FOMJCoinsChangedSignature OnCoinsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Run")
	FOMJRunFinishedSignature OnRunFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> IdleFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> RunFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> JumpFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> FallFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float JumpHeight = 650.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death")
	TSubclassOf<AActor> DeathEffectClass;

	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void OnPlayerDied();

	UFUNCTION(BlueprintImplementableEvent, Category = "Win")
	void OnPlayerWon();

private:
	void MoveLeftPressed();
	void MoveLeftReleased();
	void MoveRightPressed();
	void MoveRightReleased();
	void StartJump();
	void StopJump();
	void UpdateMovement();
	void UpdateFlipbook();
	void SetFacingDirection(float Direction);
	void FinishRun();

	bool bMoveLeftHeld = false;
	bool bMoveRightHeld = false;
	bool bIsDead = false;
	bool bHasWon = false;
	bool bRunFinished = false;
	bool bHasCheckpoint = false;
	int32 CoinsCollected = 0;
	float RunStartTime = 0.f;
	float RunEndTime = 0.f;
	FVector CheckpointLocation = FVector::ZeroVector;
};
