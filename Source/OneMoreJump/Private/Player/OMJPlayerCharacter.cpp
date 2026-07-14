#include "Player/OMJPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputCoreTypes.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

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

void AOMJPlayerCharacter::MoveLeftPressed()
{
	bMoveLeftHeld = true;
	SetFacingDirection(-1.f);
}

void AOMJPlayerCharacter::MoveLeftReleased()
{
	bMoveLeftHeld = false;
}

void AOMJPlayerCharacter::MoveRightPressed()
{
	bMoveRightHeld = true;
	SetFacingDirection(1.f);
}

void AOMJPlayerCharacter::MoveRightReleased()
{
	bMoveRightHeld = false;
}

void AOMJPlayerCharacter::StartJump()
{
	Jump();
}

void AOMJPlayerCharacter::StopJump()
{
	StopJumping();
}

void AOMJPlayerCharacter::UpdateMovement()
{
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
		if (JumpApexFlipbook && FMath::Abs(Velocity.Z) <= JumpApexVelocityThreshold)
		{
			NextFlipbook = JumpApexFlipbook;
		}
		else
		{
			NextFlipbook = Velocity.Z >= 0.f ? JumpFlipbook : FallFlipbook;
		}
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
