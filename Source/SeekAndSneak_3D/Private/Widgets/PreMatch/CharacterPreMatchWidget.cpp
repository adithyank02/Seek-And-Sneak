// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PreMatch/CharacterPreMatchWidget.h"
#include "Components/TextBlock.h"

#include "GameState/PropHuntGameState.h"
#include "Interface/Controller/ControllerInterface.h"
#include "Interface/GameState/GameStateInterface.h"


void UCharacterPreMatchWidget::NativeConstruct()
{
	SetCharacterType();

	SetPreMatchTimer();

	SetWidgetText();
}

void UCharacterPreMatchWidget::SetCharacterType()
{
	if (IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetOwningPlayer()))
	{
		PlayerCharacter = ControllerInterface->GetCharacterType();
	}
}

void UCharacterPreMatchWidget::SetPreMatchTimer()
{
	if (IGameStateInterface* Interface = Cast<IGameStateInterface>(GetWorld()->GetGameState<APropHuntGameState>()))
	{
		int32 TimerValue = Interface->GetPreMatchTimerVariable();
		PreMatchTimer->SetText(FText::AsNumber(TimerValue));
	}
}

void UCharacterPreMatchWidget::SetWidgetText()
{
	FString CharacterText;
	FString CharacterObjective;

	if (PlayerCharacter == ECharacterType::HunterCharacter)
	{
		CharacterText = FString("Hunter");
		CharacterObjective = FString("Find All The Props And Destroy It");
	}
	else
	{
        CharacterText = FString("Prop");
        CharacterObjective = FString("Hide from the hunter and survive till the end");
	}
	CharacterTypeText->SetText(FText::FromString(CharacterText));
	CharacterObjectiveText->SetText(FText::FromString(CharacterObjective));
}
