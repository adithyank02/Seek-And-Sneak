// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Sessions/FindSessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework\PlayerController.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

UFindSessionWidget::UFindSessionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget>FindingWidgetClass(TEXT("/Game/Widgets/Others/BP_FindingSessionWidget.BP_FindingSessionWidget_C"));
	ConstructorHelpers::FClassFinder<UUserWidget>ErrorWidgetClass(TEXT("/Game/Widgets/Others/BP_ErrorWidget.BP_ErrorWidget_C"));

	if (FindingWidgetClass.Succeeded())
	{
		FindingScreenClass = FindingWidgetClass.Class;
	}
	if (ErrorWidgetClass.Succeeded())
	{
		ErrorScreenClass = ErrorWidgetClass.Class;
	}
}

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
		GiveSessionCode = CommitedText.ToString();
		//Converting All Characters To Upper --- Cause The Text See Is Always Upper Even If User Type Lower
		GiveSessionCode.ToUpperInline();

		bCanStartFinding = true; 
	}
	else
	{
		ShowInvalidText();
	}
}


void UFindSessionWidget::OnFindButtonClicked()
{
	if (bCanStartFinding)
	{

	  //Disabling The Button For Avoiding Spawming
	   FindButton->SetIsEnabled(false);

	  //Showing User To Loading The Game
	   AddLoadingScreenWidget();

		if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
		{
			//Getting Session Interface According To World Context /PIE/StandAlone Etc
			IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

			if (SessionInterface.IsValid())
			{
				//Clearing All Findings When It Already Exist
				if (SessionSetting.IsValid()) SessionInterface->ClearOnFindSessionsCompleteDelegates(this);

				SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UFindSessionWidget::OnFindSessionCompleted);

				SessionSetting = MakeShareable(new FOnlineSessionSearch());

				SessionSetting->bIsLanQuery = false;
				SessionSetting->MaxSearchResults = MaxSearching;
				SessionSetting->PingBucketSize = SearchPingBucketSize;

				//Finding The Sessiong
				if (SessionInterface->FindSessions(0, SessionSetting.ToSharedRef()))return;
			}
		}
	}
	else
	{
		ShowInvalidText();
	}

}

void UFindSessionWidget::OnFindSessionCompleted(bool bIsSucess)
{
	if (bIsSucess)
	{
		if (SessionSetting->SearchResults.Num() > 0)
		{

			FString RoomCode;
			for (const FOnlineSessionSearchResult& SearchInfo : SessionSetting->SearchResults)
			{
				//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Loop Started"), true, true, FLinearColor::Blue, 5);
				if (SearchInfo.Session.SessionSettings.Get(RoomCodeKey, RoomCode))
				{
					if (GiveSessionCode == RoomCode)
					{
						UKismetSystemLibrary::PrintString(GetWorld(), TEXT("JOIN SESSION CALLED"));
						JoinSession(SearchInfo);
						return;
					}
				}
				
			}
		}
	}

	//Enableing The Join Button If Any Occurs Bad
	FindButton->SetIsEnabled(true);
	//Also Removing Loading Widget
	FindingScreenWidget->RemoveFromParent();
	//Creating Error Widget
	AddErrorScreenWidget();
}

void UFindSessionWidget::JoinSession(const FOnlineSessionSearchResult& SearchResult)
{
	FString GetSessionName;
	if (SearchResult.Session.SessionSettings.Get(SessionKey, GetSessionName))
	{
		if (IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
		{
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UFindSessionWidget::OnJoinSessionComplete);

			if (SessionInterface->JoinSession(0, FName(*GetSessionName), SearchResult))return;
		}
	}
	else
	{
		//Enableing The Join Button If Any Occurs Bad
		FindButton->SetIsEnabled(true);
		//Also Removing Loading Widget
		FindingScreenWidget->RemoveFromParent();
		//Creating Error Widget
		AddErrorScreenWidget();
	}
}

void UFindSessionWidget::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
	{
		FString ConnectToServer;
		if(SessionInterface->GetResolvedConnectString(SessionName, ConnectToServer))
		{
			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				PlayerController->ClientTravel(ConnectToServer, ETravelType::TRAVEL_Absolute);
			}
		}
	}

}

//--------------------Helper Function

void UFindSessionWidget::AddLoadingScreenWidget()
{
	if (FindingScreenClass && !FindingScreenWidget)
	{
		//Only Creating The Wiget For Once
		FindingScreenWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), FindingScreenClass);
	}
	FindingScreenWidget->AddToViewport();
}

void UFindSessionWidget::AddErrorScreenWidget()
{
	if (ErrorScreenClass)
	{
		UUserWidget* ErrorScreenWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), ErrorScreenClass);
		ErrorScreenWidget->AddToViewport();
	}	
}

void UFindSessionWidget::ShowInvalidText()
{
	RoomCodeInvalidText->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(ResetInvalidTextTimer, this, &UFindSessionWidget::ResetInvalidTextVisibility, 2, false);
	EnterSessionCode_TextBox->SetText(FText::FromString(""));
}

void UFindSessionWidget::ResetInvalidTextVisibility()
{
	RoomCodeInvalidText->SetVisibility(ESlateVisibility::Hidden);

}


