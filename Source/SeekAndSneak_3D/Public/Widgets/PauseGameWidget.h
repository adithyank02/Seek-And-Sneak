// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseGameWidget.generated.h"

class UButton;
class UTextBlock;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UPauseGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* QuitMatchButton;

	void BindButtonDelegate();

	void QuitMatchButtonClicked();

	void OnSessionDestroyed(FName SessionName, bool bWasSuccessful);
	
};
