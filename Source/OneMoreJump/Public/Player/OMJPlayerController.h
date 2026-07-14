#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OMJPlayerController.generated.h"

UCLASS(Blueprintable)
class ONEMOREJUMP_API AOMJPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPlayerHUD();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HidePlayerHUD();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetMenuInputMode();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetGameInputMode();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ContinueFromCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RestartCurrentLevel();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void QuitGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnStartMenuRequested();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnPlayerHUDShown();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnPlayerHUDHidden();
};
