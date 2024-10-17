// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemUtils.h"

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

	//For Checking UserInput Count
	const int MaxConnectionNum = 10;
	const int MinConnectionNum = 2;

	int NumberOfConnections;

	//Store Level Name For Openeing After Creating Session (Lobby Map)
	FName GamePlayLevelName;

	//RandomCode Length 
	const int CodeLength = 6;

	//Setting A Code Value To This Key
	const FName RoomCodeKey = FName("RoomCode");

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TotalPlayerNum_TextBox;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CreateButton;

	UFUNCTION()
	void HandleTextBoxCommited(const FText& CommitedText, ETextCommit::Type CommitedType);

	UFUNCTION()
	void OnCreateButtonClicked();


	//Game Should Always Run For Lan
	const bool IsLan = true;
	const bool BShouldAdvertise = true;
	const bool BJoinOnProgress = false;
	const bool BUsePresence = true;

	//Session Handling
	FOnlineSessionSettings OnlineSessionSettings;

	//Function That Trigger After Session Creation 
	void OnSessionCreateCompleted(FName SessionName , bool bWasSuccessful);

	//For Generating The Random Code
	const FString Characters = TEXT("A1B2C3D4E5F6G7H8I9J0KL0M9N8O7P6Q5R4S3T2U1V0WXYZ");

	const int StringTotalLength = Characters.Len();
	//Function Generating The Code
	FString RandomSessionCodeGenerator();
};
