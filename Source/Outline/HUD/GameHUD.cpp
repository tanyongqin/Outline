// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "CharacterOverlay.h"
#include "GameOver.h"
#include "GameFramework/PlayerController.h"

void AGameHUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (IsValid(PlayerController) && IsValid(CharacterOverlayClass))
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
		CharacterOverlay->AddToViewport();
	}
}

void AGameHUD::AddGameOver(bool bIsWin)
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (IsValid(PlayerController) && IsValid(GameOverClass))
	{
		GameOver = CreateWidget<UGameOver>(PlayerController, GameOverClass);
		GameOver->AddToViewport();
		GameOver->Setup();
		GameOver->AnnounaceTextEnable(bIsWin);

		// ���ý��㵽UserWidget
		// GameOver->SetUserFocus(PlayerController);

		// ��������ģʽΪ���
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(GameOver->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
	}
}
