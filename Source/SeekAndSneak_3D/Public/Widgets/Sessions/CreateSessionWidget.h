// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "CreateSessionWidget.generated.h"

class UEditableTextBox;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UCreateSessionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

private:

	const int MaxConnectionNum = 10;
	const int MinConnectionNum = 2; 

	int NumberOfConnections;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TotalPlayerNum_TextBox;

	UFUNCTION()
	void HandleTextBoxCommited(const FText& CommitedText, ETextCommit::Type CommitedType);

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CreateButton;

	UFUNCTION()
	void OnCreateButtonClicked();


	FName GamePlayLevelName;

	//Game Should Always Run For Lan
	const bool IsLan = true;
	const bool ShouldAdvertise = true;
	const bool bJoinOnProgress = false;
	const bool bUsePresence = false;

	//Session Handling
	FOnlineSessionSettings OnlineSessionSettings;

	//Function That Trigger After Session Creation 
	void OnSessionCreateCompleted(FName SessionName , bool WasSuccessful);

	//Button Trigger More Than Once
	bool CallOnce = true;

	//RandomCode Length 
	const int CodeLength = 6;

	//For Generating The Random Code

	const FString Characters = TEXT("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	const int StringTotalLength = Characters.Len();

	FString RandomSessionCodeGenerator();


	
};
