// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

UCLASS()
class OUTLINE_API UGameOver : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup();

	void AnnounaceTextEnable(bool bIsWin);
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Win;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Fail;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UFUNCTION()
	void OnClickExit();
};
