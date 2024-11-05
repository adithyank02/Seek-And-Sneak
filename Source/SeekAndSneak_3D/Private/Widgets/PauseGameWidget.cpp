// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseGameWidget.h"

#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/TextBlock.h"

#include "Interface/GameInstance/PropHuntGameInstInterface.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemUtils.h"

#include "Kismet/GameplayStatics.h"

void UPauseGameWidget::NativeConstruct()
{
	BindButtonDelegate();

}

void UPauseGameWidget::BindButtonDelegate()
{
	QuitMatchButton->BaseButtonClicked.BindUObject(this, &UPauseGameWidget::QuitMatchButtonClicked);
}

void UPauseGameWidget::QuitMatchButtonClicked()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem) return;

	IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (SessionInterface.IsValid())
	{
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPauseGameWidget::OnSessionDestroyed);
		
		SessionInterface->DestroySession(Session_Name);
	}
}

void UPauseGameWidget::OnSessionDestroyed(FName SessionName, bool bWasSuccessful)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("BaseMap"));
}
