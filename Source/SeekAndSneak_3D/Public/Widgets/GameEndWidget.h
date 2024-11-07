// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

class UButton;
class UTextBlock;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	//const Session Name
	const FName Session_Name = FName("SESSION_NAME");

protected:

	void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
    UButtonBaseWidget* RestartMatchButton;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* QuitMatchButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClientGameEndText;

	void BindButtonDelegate();

	void RestartMatchButtonClicked();
	void QuitMatchButtonClicked();

	void OnSessionDestroyed(FName SessionName, bool bWasSuccessful);
	
};
