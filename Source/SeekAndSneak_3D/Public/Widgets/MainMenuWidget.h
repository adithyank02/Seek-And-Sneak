// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "MainMenuWidget.generated.h"

class UVerticalBox;
class UEditableTextBox;
class UWidgetSwitcher;
class USessionWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

private:

	void NativeConstruct()override;


	TSubclassOf<USessionWidget>SessionWidgetClass;

	//Components For Setting Main Menu UI

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CreateSessionButton;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* ExitGameButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EnterNameEditableBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LongNameWarningText;

	FString Player_InGameName;

	const int PlayerNameMaxLen = 9;

	UFUNCTION()
	void OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnCreateSessionButtonClicked();
	UFUNCTION()
	void OnExitGameButtonClicked();

	//Widget Switcher
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	//UPROPERTY(meta = (BindWidget))
	USessionWidget* SessionWidget;

	UFUNCTION()
	void SessionWidgetBackButton();
	
	//Helper Function

	void ShowPlayerNameError();

	void CheckForSavedPlayerName();

	//For Checking The Player Name Contain WhiteSpace Or Not
	bool DoesContainWhiteSpace();
};

