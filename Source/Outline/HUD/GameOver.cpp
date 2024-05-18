// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOver::Setup()
{
	if (Btn_Exit && !Btn_Exit->OnClicked.IsBound())
	{
		Btn_Exit->OnClicked.AddDynamic(this, &UGameOver::OnClickExit);
	}
}

void UGameOver::AnnounaceTextEnable(bool bIsWin)
{
	if (bIsWin)
	{
		Txt_Win->SetVisibility(ESlateVisibility::Visible);
		Txt_Fail->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Txt_Win->SetVisibility(ESlateVisibility::Hidden);
		Txt_Fail->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGameOver::OnClickExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
