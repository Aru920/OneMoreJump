#include "Player/OMJPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/OMJPlayerCharacter.h"

void AOMJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetMenuInputMode();
	OnStartMenuRequested();
}

void AOMJPlayerController::StartGame()
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(GetPawn()))
	{
		PlayerCharacter->StartRun();
	}

	SetGameInputMode();
	ShowPlayerHUD();
}

void AOMJPlayerController::ShowPlayerHUD()
{
	OnPlayerHUDShown();
}

void AOMJPlayerController::HidePlayerHUD()
{
	OnPlayerHUDHidden();
}

void AOMJPlayerController::SetMenuInputMode()
{
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void AOMJPlayerController::SetGameInputMode()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}

void AOMJPlayerController::ContinueFromCheckpoint()
{
	if (AOMJPlayerCharacter* PlayerCharacter = Cast<AOMJPlayerCharacter>(GetPawn()))
	{
		PlayerCharacter->RespawnAtCheckpoint();
		SetGameInputMode();
		ShowPlayerHUD();
	}
}

void AOMJPlayerController::RestartCurrentLevel()
{
	const FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void AOMJPlayerController::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}
