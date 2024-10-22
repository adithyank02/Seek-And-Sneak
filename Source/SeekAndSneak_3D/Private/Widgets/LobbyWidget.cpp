// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LobbyWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Interface/GameInstance/PropHuntGameInstInterface.h"

void ULobbyWidget::NativeConstruct()
{
	StartMatchButton->BaseButtonClicked.BindUObject(this, &ULobbyWidget::StartMatchButtonClicked);

	if (IPropHuntGameInstInterface* Interface = Cast<IPropHuntGameInstInterface>(GetGameInstance()))
	{
		FString StrCode = Interface->GetRoomId();
		if (!StrCode.IsEmpty())
		{
			//HostingPlayer -- Server Side
			RoomCodeText->SetText(FText::FromString(StrCode));
			WaitToGameStartText->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			//Joining Player --- Clinet Side
			IdText->SetVisibility(ESlateVisibility::Hidden);
			RoomCodeText->SetVisibility(ESlateVisibility::Hidden);
			StartMatchButton->SetVisibility(ESlateVisibility::Hidden);
			
		}
	}
	
}

void ULobbyWidget::StartMatchButtonClicked()
{
	GetWorld()->ServerTravel(("/Game/Maps/SampleMatchLevel1?listen"), true);
}
