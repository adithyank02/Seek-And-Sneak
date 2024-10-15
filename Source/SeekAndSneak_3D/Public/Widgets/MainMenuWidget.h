// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "MainMenuWidget.generated.h"

class UVerticalBox;
class UWidgetSwitcher;
class USessionWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	void NativeConstruct()override;

	//Components For Setting Main Menu UI

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CreateSessionButton;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* ExitGameButton;

	UFUNCTION()
	void OnCreateSessionButtonClicked();
	UFUNCTION()
	void OnExitGameButtonClicked();

	//Widget Switcher
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	USessionWidget* SessionWidget;

	UFUNCTION()
	void SessionWidgetBackButton();
};
