// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LobbyWidget.h"
#include "Components/TextBlock.h"
#include "Interface/GameInstance/PropHuntGameInstInterface.h"

void ULobbyWidget::NativeConstruct()
{
	if (IPropHuntGameInstInterface* Interface = Cast<IPropHuntGameInstInterface>(GetGameInstance()))
	{
		FString StrCode = Interface->GetRoomId();
		if (!StrCode.IsEmpty())
		{
			RoomCodeText->SetText(FText::FromString(StrCode));
		}
		else
		{
			RoomCodeText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}
