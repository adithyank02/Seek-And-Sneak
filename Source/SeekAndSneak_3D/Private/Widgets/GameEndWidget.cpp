// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameEndWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/TextBlock.h"

#include "Interface/GameInstance/PropHuntGameInstInterface.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemUtils.h"

#include "Kismet/GameplayStatics.h"

void UGameEndWidget::NativeConstruct()
{
	BindButtonDelegate();

	if (GetOwningPlayer()->HasAuthority())
	{
		ClientGameEndText->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		RestartMatchButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGameEndWidget::BindButtonDelegate()
{
	RestartMatchButton->BaseButtonClicked.BindUObject(this, &UGameEndWidget::RestartMatchButtonClicked);
	QuitMatchButton->BaseButtonClicked.BindUObject(this, &UGameEndWidget::QuitMatchButtonClicked);
}

void UGameEndWidget::RestartMatchButtonClicked()
{
	GetWorld()->ServerTravel(("/Game/Maps/CityMarket_Map?listen"), true);
}

void UGameEndWidget::QuitMatchButtonClicked()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem) return;

	IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (SessionInterface.IsValid())
	{
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UGameEndWidget::OnSessionDestroyed);
	
			SessionInterface->DestroySession(Session_Name);		
	}
}

void UGameEndWidget::OnSessionDestroyed(FName SessionName, bool bWasSuccessful)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("BaseMap"));
}


