// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UTextBlock;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct()override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* IdText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomCodeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaitToGameStartText;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* StartMatchButton;

	UFUNCTION()
	void StartMatchButtonClicked();
	
};
