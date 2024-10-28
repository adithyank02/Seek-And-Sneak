// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WinnerWidget/WinnerShowingWidget.h"
#include "Components/TextBlock.h"
#include "Interface/Controller/ControllerInterface.h"

void UWinnerShowingWidget::NativeConstruct()
{
	if (IControllerInterface* Interface = Cast<IControllerInterface>(GetOwningPlayer()))
	{
		MatchWinnerCharacterType = Interface->GetWinnerCharacterType();
	}
	SetAnnouncingText();
}

void UWinnerShowingWidget::SetAnnouncingText()
{
	FString AnnouncingString;
	if (MatchWinnerCharacterType == ECharacterType::HunterCharacter)
	{
		AnnouncingString = HunterWinningText;
	}
	else
	{
		AnnouncingString = PropWinningText;
	}
	WinnerAnnouncingText->SetText(FText::FromString(AnnouncingString));
}
