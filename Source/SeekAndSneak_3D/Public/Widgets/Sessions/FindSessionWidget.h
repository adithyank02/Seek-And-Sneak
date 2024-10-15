// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemTypes.h"

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

protected:

	void NativeConstruct()override;

private:

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EnterSessionCode_TextBox;

	UFUNCTION()
	void SessionCode_TextBoxCommited(const FText& CommitedText, ETextCommit::Type CommitType);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomCodeInvalidText;

	FTimerHandle ResetInvalidTextTimer;
	void ResetInvalidTextVisibility();

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* FindButton;

	UFUNCTION()
	void OnFindButtonClicked();

	//Find And Join Session Managment

	const int RoomCodeLength = 8;
	int GiveSessionCode;

	const bool LanQuery = true;
	const int MaxSearching = 5;
	const int SearchPingBucketSize = 50;

	void OnFindSessionCompleted(bool bIsSucess);
	
};
