// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemTypes.h"
#include "OnlineSubsystemUtils.h"

#include "FindSessionWidget.generated.h"

class UEditableTextBox;
class UButtonBaseWidget;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UFindSessionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFindSessionWidget(const FObjectInitializer& ObjectInitializer);

protected:

	void NativeConstruct()override;

private:

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EnterSessionCode_TextBox;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* FindButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomCodeInvalidText;


	UFUNCTION()
	void SessionCode_TextBoxCommited(const FText& CommitedText, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnFindButtonClicked();

	//Pointer To Loading Widget
	UPROPERTY()
	UUserWidget*FindingScreenWidget;

	//Loading Screen WidgetClass
	UPROPERTY()
	TSubclassOf<UUserWidget>FindingScreenClass;

	UPROPERTY()
	TSubclassOf<UUserWidget>ErrorScreenClass;

	void AddLoadingScreenWidget();
	void AddErrorScreenWidget();

	//Variable For Starting The FindSession
	bool bCanStartFinding;

	void ShowInvalidText();

	FTimerHandle ResetInvalidTextTimer;
	void ResetInvalidTextVisibility();

	//Find And Join Session Managment
	TSharedPtr<FOnlineSessionSearch>SessionSetting;

	//For Verying From The UserInput
	const int RoomCodeLength = 6;
	FString GiveSessionCode;

	//For Finding The RoomCode Stored In The Key On SessionSettings
	const FName RoomCodeKey = FName("RoomCode");
	//For Finding Session Name 
	const FName SessionKey = FName("SESSIONKEY");

	const bool LanQuery = true;
	const int MaxSearching = 5;
	const int SearchPingBucketSize = 50;

	void OnFindSessionCompleted(bool bIsSucess);

	void JoinSession(const FOnlineSessionSearchResult& SearchResult);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
};
