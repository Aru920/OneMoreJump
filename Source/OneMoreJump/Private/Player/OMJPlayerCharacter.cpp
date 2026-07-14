#include "Player/OMJPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputCoreTypes.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Player/OMJPlayerController.h"

AOMJPlayerCharacter::AOMJPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	FollowCamera->OrthoWidth = 960.f;

	JumpMaxCount = 2;
	GetCharacterMovement()->JumpZVelocity = JumpHeight;
	GetCharacterMovement()->AirControl = 1.f;
}

void AOMJPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->JumpZVelocity = JumpHeight;
	RunStartTime = GetWorld()->GetTimeSeconds();
	GetCharacterMovement()->DisableMovement();

	if (IdleFlipbook)
	{
		GetSprite()->SetFlipbook(IdleFlipbook);
	}
}

void AOMJPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateMovement();
	UpdateFlipbook();
}

void AOMJPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::A, IE_Pressed, this, &AOMJPlayerCharacter::MoveLeftPressed);
	PlayerInputComponent->BindKey(EKeys::A, IE_Released, this, &AOMJPlayerCharacter::MoveLeftReleased);
	PlayerInputComponent->BindKey(EKeys::D, IE_Pressed, this, &AOMJPlayerCharacter::MoveRightPressed);
	PlayerInputComponent->BindKey(EKeys::D, IE_Released, this, &AOMJPlayerCharacter::MoveRightReleased);
	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &AOMJPlayerCharacter::StartJump);
	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Released, this, &AOMJPlayerCharacter::StopJump);
}

void AOMJPlayerCharacter::Die()
{
	if (bIsDead || bHasWon)
	{
		return;
	}

	bIsDead = true;
	bMoveLeftHeld = false;
	bMoveRightHeld = false;

	if (DeathEffectClass)
	{
		GetWorld()->SpawnActor<AActor>(DeathEffectClass, GetActorTransform());
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GetCharacterMovement()->DisableMovement();

	if (AOMJPlayerController* PlayerController = Cast<AOMJPlayerController>(GetController()))
	{
		PlayerController->HidePlayerHUD();
	}

	OnPlayerDied();
}

void AOMJPlayerCharacter::Win()
{
	if (bIsDead || bHasWon)
	{
		return;
	}

	bHasWon = true;
	bMoveLeftHeld = false;
	bMoveRightHeld = false;

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	if (IdleFlipbook)
	{
		GetSprite()->SetFlipbook(IdleFlipbook);
	}

	FinishRun();

	if (AOMJPlayerController* PlayerController = Cast<AOMJPlayerController>(GetController()))
	{
		PlayerController->HidePlayerHUD();
	}

	OnPlayerWon();
}

void AOMJPlayerCharacter::StartRun()
{
	if (bIsDead || bHasWon)
	{
		return;
	}

	bWaitingForStart = false;
	bRunFinished = false;
	RunStartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AOMJPlayerCharacter::SetCheckpointLocation(FVector NewCheckpointLocation)
{
	CheckpointLocation = NewCheckpointLocation;
	bHasCheckpoint = true;
}

void AOMJPlayerCharacter::RespawnAtCheckpoint()
{
	if (!bHasCheckpoint)
	{
		return;
	}

	SetActorLocation(CheckpointLocation);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	bIsDead = false;
}

void AOMJPlayerCharacter::CollectCoin()
{
	if (bWaitingForStart || bIsDead || bHasWon)
	{
		return;
	}

	++CoinsCollected;
	OnCoinsChanged.Broadcast(CoinsCollected);
}

int32 AOMJPlayerCharacter::GetCoinsCollected() const
{
	return CoinsCollected;
}

float AOMJPlayerCharacter::GetElapsedTime() const
{
	if (bWaitingForStart || !GetWorld())
	{
		return 0.f;
	}

	return (bRunFinished ? RunEndTime : GetWorld()->GetTimeSeconds()) - RunStartTime;
}

int32 AOMJPlayerCharacter::GetElapsedMinutes() const
{
	return FMath::FloorToInt(GetElapsedTime()) / 60;
}

int32 AOMJPlayerCharacter::GetElapsedSeconds() const
{
	return FMath::FloorToInt(GetElapsedTime()) % 60;
}

bool AOMJPlayerCharacter::HasCheckpoint() const
{
	return bHasCheckpoint;
}

void AOMJPlayerCharacter::MoveLeftPressed()
{
	if (bWaitingForStart || bIsDead || bHasWon)
	{
		return;
	}

	bMoveLeftHeld = true;
	SetFacingDirection(-1.f);
}

void AOMJPlayerCharacter::MoveLeftReleased()
{
	bMoveLeftHeld = false;
}

void AOMJPlayerCharacter::MoveRightPressed()
{
	if (bWaitingForStart || bIsDead || bHasWon)
	{
		return;
	}

	bMoveRightHeld = true;
	SetFacingDirection(1.f);
}

void AOMJPlayerCharacter::MoveRightReleased()
{
	bMoveRightHeld = false;
}

void AOMJPlayerCharacter::StartJump()
{
	if (bWaitingForStart || bIsDead || bHasWon)
	{
		return;
	}

	Jump();
}

void AOMJPlayerCharacter::StopJump()
{
	StopJumping();
}

void AOMJPlayerCharacter::UpdateMovement()
{
	if (bWaitingForStart || bIsDead || bHasWon)
	{
		return;
	}

	const float MoveValue = (bMoveRightHeld ? 1.f : 0.f) - (bMoveLeftHeld ? 1.f : 0.f);
	if (!FMath::IsNearlyZero(MoveValue))
	{
		AddMovementInput(FVector::XAxisVector, MoveValue);
	}
}

void AOMJPlayerCharacter::UpdateFlipbook()
{
	UPaperFlipbook* NextFlipbook = IdleFlipbook;
	const FVector Velocity = GetVelocity();

	if (GetCharacterMovement()->IsFalling())
	{
		NextFlipbook = Velocity.Z >= 0.f ? JumpFlipbook : FallFlipbook;
	}
	else if (!FMath::IsNearlyZero(Velocity.X, 5.f))
	{
		NextFlipbook = RunFlipbook;
	}

	if (NextFlipbook && GetSprite()->GetFlipbook() != NextFlipbook)
	{
		GetSprite()->SetFlipbook(NextFlipbook);
	}
}

void AOMJPlayerCharacter::SetFacingDirection(float Direction)
{
	if (FMath::IsNearlyZero(Direction))
	{
		return;
	}

	FVector CurrentSpriteScale = GetSprite()->GetRelativeScale3D();
	CurrentSpriteScale.X = FMath::Abs(CurrentSpriteScale.X) * FMath::Sign(Direction);
	GetSprite()->SetRelativeScale3D(CurrentSpriteScale);
}

void AOMJPlayerCharacter::FinishRun()
{
	if (bRunFinished)
	{
		return;
	}

	bRunFinished = true;
	RunEndTime = GetWorld() ? GetWorld()->GetTimeSeconds() : RunStartTime;
	OnRunFinished.Broadcast(GetElapsedTime(), CoinsCollected);
}
