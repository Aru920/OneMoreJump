#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "OMJPlayerCharacter.generated.h"

class UCameraComponent;
class UPaperFlipbook;
class USpringArmComponent;

UCLASS(Blueprintable)
class ONEMOREJUMP_API AOMJPlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AOMJPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

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
	TObjectPtr<UPaperFlipbook> JumpApexFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> FallFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	float JumpApexVelocityThreshold = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float JumpHeight = 650.f;

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

	bool bMoveLeftHeld = false;
	bool bMoveRightHeld = false;
};
