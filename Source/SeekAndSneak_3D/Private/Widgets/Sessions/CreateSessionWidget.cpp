// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Sessions/CreateSessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/EditableTextBox.h"
#include "Interface/GameInstance/PropHuntGameInstInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UCreateSessionWidget::NativeConstruct()
{
	CreateButton->BaseButtonClicked.BindUObject(this, &UCreateSessionWidget::OnCreateButtonClicked);

	TotalPlayerNum_TextBox->OnTextCommitted.AddDynamic(this, &UCreateSessionWidget::HandleTextBoxCommited);

	NumberOfConnections = 2; 

}

void UCreateSessionWidget::HandleTextBoxCommited(const FText& CommitedText, ETextCommit::Type CommitedType)
{
	FString TextToString = CommitedText.ToString();

	bool bContainNum = TextToString.IsNumeric();
	if (bContainNum)
	{
		int Value = FCString::Atoi(*TextToString);
		NumberOfConnections = FMath::Clamp(Value, MinConnectionNum, MaxConnectionNum);
	}
	else
	{
		//Setting Default Value If Not Value Is Entered
		NumberOfConnections = MinConnectionNum;
	}

	TotalPlayerNum_TextBox->SetText(FText::FromString(FString::FromInt(NumberOfConnections)));

}

void UCreateSessionWidget::OnCreateButtonClicked()
{
	CreateButton->SetIsEnabled(false);

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		//IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCreateSessionWidget::OnSessionCreateCompleted);

			OnlineSessionSettings.bIsLANMatch = IsLan;
			OnlineSessionSettings.NumPublicConnections = NumberOfConnections;
			OnlineSessionSettings.bShouldAdvertise = BShouldAdvertise;
			OnlineSessionSettings.bAllowJoinInProgress = BJoinOnProgress;
			OnlineSessionSettings.bUsesPresence = false;
			
			//It Is Sending In The For Of Key Value Pair 
			FString RoomCode = RandomSessionCodeGenerator();
			OnlineSessionSettings.Set(RoomCodeKey/*Key*/, RoomCode/*Value*/, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

			//Creating A Key For  Session Name
			FName SessionKey = FName("SESSIONKEY");

			//Setting Session Name For Make Use To Join The Session
			OnlineSessionSettings.Set(SessionKey, Session_Name.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

			if (IPropHuntGameInstInterface* GameInstanceInterface = Cast<IPropHuntGameInstInterface>(GetGameInstance()))
			{
				//Setting The Room Id
				GameInstanceInterface->SetRoomId(RoomCode);

				if (SessionInterface->CreateSession(0, Session_Name, OnlineSessionSettings))return;
			}
		}
	}

}

void UCreateSessionWidget::OnSessionCreateCompleted(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		//Name Of The Map
		FName LevelName = FName("TempMap");
		//Setting The Level Has Clinet Supported
		FString Option = "listen";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName,true, Option);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SOMETHING WENT WRONG !!! PLEASE TRY AGAIN"), true, true, FLinearColor::Red, 5);
		CreateButton->SetIsEnabled(true);
	}
}

FString UCreateSessionWidget::RandomSessionCodeGenerator()
{
	FString GeneratedCode;

	for (int Itr = 1; Itr <= CodeLength; Itr++)
	{
		int Index = FMath::RandRange(0, StringTotalLength-1);
		GeneratedCode += Characters[Index];
	}
	UKismetSystemLibrary::PrintString(GetWorld(),GeneratedCode, true, true, FLinearColor::Yellow, 60);
	return GeneratedCode;
}

