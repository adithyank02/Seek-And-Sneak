// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Sessions/FindSessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "Online/OnlineSessionNames.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UFindSessionWidget::NativeConstruct()
{
	RoomCodeInvalidText->SetVisibility(ESlateVisibility::Hidden);

	FindButton->BaseButtonClicked.BindUObject(this, &UFindSessionWidget::OnFindButtonClicked);

	EnterSessionCode_TextBox->OnTextCommitted.AddDynamic(this, &UFindSessionWidget::SessionCode_TextBoxCommited);
}


void UFindSessionWidget::SessionCode_TextBoxCommited(const FText& CommitedText, ETextCommit::Type CommitType)
{
	int CodeLength = CommitedText.ToString().Len();

	if (CodeLength == RoomCodeLength)
	{
		GiveSessionCode = FCString::Atoi(*CommitedText.ToString());
	}
	else
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Room Code Invalid"));
		RoomCodeInvalidText->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(ResetInvalidTextTimer, this, &UFindSessionWidget::ResetInvalidTextVisibility,2,false);
		EnterSessionCode_TextBox->SetText(FText::FromString(""));
	}

}

void UFindSessionWidget::ResetInvalidTextVisibility()
{
	RoomCodeInvalidText->SetVisibility(ESlateVisibility::Hidden);

}

void UFindSessionWidget::OnFindButtonClicked()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UFindSessionWidget::OnFindSessionCompleted);

			TSharedPtr<FOnlineSessionSearch>SessionSetting = MakeShareable(new FOnlineSessionSearch());

			SessionSetting->MaxSearchResults = MaxSearching;
			SessionSetting->PingBucketSize = SearchPingBucketSize;

			SessionSetting->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

			SessionInterface->FindSessions(0, SessionSetting.ToSharedRef());
		}
	}
}

void UFindSessionWidget::OnFindSessionCompleted(bool bIsSucess)
{
	if (bIsSucess)
	{

	}
	else
	{
		
	}
}

