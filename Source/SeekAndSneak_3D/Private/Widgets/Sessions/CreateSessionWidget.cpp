// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Sessions/CreateSessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/EditableTextBox.h"
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

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%d"), NumberOfConnections), true, true, FLinearColor::White, 5);

}

void UCreateSessionWidget::OnCreateButtonClicked()
{
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
			OnlineSessionSettings.Set(RoomCodeKey/*Key*/, RandomSessionCodeGenerator()/*Value*/, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
			
			//Setting Session Name Has Local System Name
			FName SessionName = FPlatformProcess::ComputerName();

			if (SessionInterface->CreateSession(0, SessionName, OnlineSessionSettings))return;

			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Every Thing Fine"), true, true, FLinearColor::Green);
			
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

		UKismetSystemLibrary::PrintString(GetWorld(), SessionName.ToString(), true, true, FLinearColor::Blue, 5);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SOMETHING WENT WRONG !!! PLEASE TRY AGAIN"), true, true, FLinearColor::Red, 5);
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

